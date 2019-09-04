#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct smscore_device_t {scalar_t__ mode; int fw_version; int /*<<< orphan*/  ir_init_done; int /*<<< orphan*/  gpio_get_level_done; int /*<<< orphan*/  gpio_get_res; int /*<<< orphan*/  gpio_set_level_done; int /*<<< orphan*/  gpio_configuration_done; int /*<<< orphan*/  resume_done; int /*<<< orphan*/  trigger_done; int /*<<< orphan*/  data_download_done; int /*<<< orphan*/  data_validity_done; int /*<<< orphan*/  reload_start_done; int /*<<< orphan*/  init_device_done; int /*<<< orphan*/  version_ex_done; int /*<<< orphan*/  modes_supported; } ;
struct smscore_client_t {int (* onresponse_handler ) (int /*<<< orphan*/ ,struct smscore_buffer_t*) ;int /*<<< orphan*/  context; } ;
struct smscore_buffer_t {int offset; scalar_t__ size; scalar_t__ p; } ;
struct sms_version_res {int firmware_id; int rom_ver_major; int rom_ver_minor; int /*<<< orphan*/  supported_protocols; } ;
struct sms_msg_hdr {int msg_type; scalar_t__ msg_length; int /*<<< orphan*/  msg_dst_id; } ;
struct sms_msg_data {int /*<<< orphan*/ * msg_data; } ;

/* Variables and functions */
 scalar_t__ DEVICE_MODE_DVBT_BDA ; 
 int DEVICE_MODE_NONE ; 
 int /*<<< orphan*/  DVBT_BDA_CONTROL_MSG_ID ; 
 int EBUSY ; 
#define  MSG_SMS_DATA_DOWNLOAD_RES 148 
#define  MSG_SMS_DATA_VALIDITY_RES 147 
#define  MSG_SMS_DVBT_BDA_DATA 146 
#define  MSG_SMS_GET_VERSION_EX_RES 145 
#define  MSG_SMS_GPIO_CONFIG_EX_RES 144 
#define  MSG_SMS_GPIO_GET_LEVEL_RES 143 
#define  MSG_SMS_GPIO_SET_LEVEL_RES 142 
 int MSG_SMS_HO_PER_SLICES_IND ; 
#define  MSG_SMS_INIT_DEVICE_RES 141 
#define  MSG_SMS_INTERFACE_LOCK_IND 140 
#define  MSG_SMS_INTERFACE_UNLOCK_IND 139 
#define  MSG_SMS_IR_SAMPLES_IND 138 
#define  MSG_SMS_ISDBT_TUNE_RES 137 
#define  MSG_SMS_NO_SIGNAL_IND 136 
#define  MSG_SMS_RF_TUNE_RES 135 
#define  MSG_SMS_SIGNAL_DETECTED_IND 134 
#define  MSG_SMS_SLEEP_RESUME_COMP_IND 133 
#define  MSG_SMS_SPI_INT_LINE_SET_RES 132 
#define  MSG_SMS_START_IR_RES 131 
#define  MSG_SMS_SWDOWNLOAD_TRIGGER_RES 130 
 int MSG_SMS_TRANSMISSION_IND ; 
#define  MSG_SW_RELOAD_EXEC_RES 129 
#define  MSG_SW_RELOAD_START_RES 128 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 unsigned long jiffies_to_msecs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int,...) ; 
 int /*<<< orphan*/  sms_ir_event (struct smscore_device_t*,char const*,int) ; 
 struct smscore_client_t* smscore_find_client (struct smscore_device_t*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smscore_putbuffer (struct smscore_device_t*,struct smscore_buffer_t*) ; 
 int /*<<< orphan*/  smscore_translate_msg (int) ; 
 int stub1 (int /*<<< orphan*/ ,struct smscore_buffer_t*) ; 

void smscore_onresponse(struct smscore_device_t *coredev,
		struct smscore_buffer_t *cb) {
	struct sms_msg_hdr *phdr = (struct sms_msg_hdr *) ((u8 *) cb->p
			+ cb->offset);
	struct smscore_client_t *client;
	int rc = -EBUSY;
	static unsigned long last_sample_time; /* = 0; */
	static int data_total; /* = 0; */
	unsigned long time_now = jiffies_to_msecs(jiffies);

	if (!last_sample_time)
		last_sample_time = time_now;

	if (time_now - last_sample_time > 10000) {
		pr_debug("data rate %d bytes/secs\n",
			  (int)((data_total * 1000) /
				(time_now - last_sample_time)));

		last_sample_time = time_now;
		data_total = 0;
	}

	data_total += cb->size;
	/* Do we need to re-route? */
	if ((phdr->msg_type == MSG_SMS_HO_PER_SLICES_IND) ||
			(phdr->msg_type == MSG_SMS_TRANSMISSION_IND)) {
		if (coredev->mode == DEVICE_MODE_DVBT_BDA)
			phdr->msg_dst_id = DVBT_BDA_CONTROL_MSG_ID;
	}


	client = smscore_find_client(coredev, phdr->msg_type, phdr->msg_dst_id);

	/* If no client registered for type & id,
	 * check for control client where type is not registered */
	if (client)
		rc = client->onresponse_handler(client->context, cb);

	if (rc < 0) {
		switch (phdr->msg_type) {
		case MSG_SMS_ISDBT_TUNE_RES:
			break;
		case MSG_SMS_RF_TUNE_RES:
			break;
		case MSG_SMS_SIGNAL_DETECTED_IND:
			break;
		case MSG_SMS_NO_SIGNAL_IND:
			break;
		case MSG_SMS_SPI_INT_LINE_SET_RES:
			break;
		case MSG_SMS_INTERFACE_LOCK_IND:
			break;
		case MSG_SMS_INTERFACE_UNLOCK_IND:
			break;
		case MSG_SMS_GET_VERSION_EX_RES:
		{
			struct sms_version_res *ver =
				(struct sms_version_res *) phdr;
			pr_debug("Firmware id %d prots 0x%x ver %d.%d\n",
				  ver->firmware_id, ver->supported_protocols,
				  ver->rom_ver_major, ver->rom_ver_minor);

			coredev->mode = ver->firmware_id == 255 ?
				DEVICE_MODE_NONE : ver->firmware_id;
			coredev->modes_supported = ver->supported_protocols;
			coredev->fw_version = ver->rom_ver_major << 8 |
					      ver->rom_ver_minor;

			complete(&coredev->version_ex_done);
			break;
		}
		case MSG_SMS_INIT_DEVICE_RES:
			complete(&coredev->init_device_done);
			break;
		case MSG_SW_RELOAD_START_RES:
			complete(&coredev->reload_start_done);
			break;
		case MSG_SMS_DATA_VALIDITY_RES:
		{
			struct sms_msg_data *validity = (struct sms_msg_data *) phdr;

			pr_debug("MSG_SMS_DATA_VALIDITY_RES, checksum = 0x%x\n",
				validity->msg_data[0]);
			complete(&coredev->data_validity_done);
			break;
		}
		case MSG_SMS_DATA_DOWNLOAD_RES:
			complete(&coredev->data_download_done);
			break;
		case MSG_SW_RELOAD_EXEC_RES:
			break;
		case MSG_SMS_SWDOWNLOAD_TRIGGER_RES:
			complete(&coredev->trigger_done);
			break;
		case MSG_SMS_SLEEP_RESUME_COMP_IND:
			complete(&coredev->resume_done);
			break;
		case MSG_SMS_GPIO_CONFIG_EX_RES:
			complete(&coredev->gpio_configuration_done);
			break;
		case MSG_SMS_GPIO_SET_LEVEL_RES:
			complete(&coredev->gpio_set_level_done);
			break;
		case MSG_SMS_GPIO_GET_LEVEL_RES:
		{
			u32 *msgdata = (u32 *) phdr;
			coredev->gpio_get_res = msgdata[1];
			pr_debug("gpio level %d\n",
					coredev->gpio_get_res);
			complete(&coredev->gpio_get_level_done);
			break;
		}
		case MSG_SMS_START_IR_RES:
			complete(&coredev->ir_init_done);
			break;
		case MSG_SMS_IR_SAMPLES_IND:
			sms_ir_event(coredev,
				(const char *)
				((char *)phdr
				+ sizeof(struct sms_msg_hdr)),
				(int)phdr->msg_length
				- sizeof(struct sms_msg_hdr));
			break;

		case MSG_SMS_DVBT_BDA_DATA:
			/*
			 * It can be received here, if the frontend is
			 * tuned into a valid channel and the proper firmware
			 * is loaded. That happens when the module got removed
			 * and re-inserted, without powering the device off
			 */
			break;

		default:
			pr_debug("message %s(%d) not handled.\n",
				  smscore_translate_msg(phdr->msg_type),
				  phdr->msg_type);
			break;
		}
		smscore_putbuffer(coredev, cb);
	}
}