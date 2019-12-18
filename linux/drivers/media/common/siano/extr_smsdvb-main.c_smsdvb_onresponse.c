#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {TYPE_1__* stat; } ;
struct dtv_frontend_properties {TYPE_2__ block_error; } ;
struct dvb_frontend {struct dtv_frontend_properties dtv_property_cache; } ;
struct smsdvb_client_t {int has_tuned; int fe_status; scalar_t__ last_per; int /*<<< orphan*/  stats_done; int /*<<< orphan*/  coredev; int /*<<< orphan*/  tune_done; int /*<<< orphan*/  demux; int /*<<< orphan*/  feed_users; struct dvb_frontend frontend; } ;
struct smscore_buffer_t {int offset; int /*<<< orphan*/  size; scalar_t__ p; } ;
struct sms_msg_hdr {int msg_type; } ;
struct TYPE_3__ {scalar_t__ uvalue; } ;

/* Variables and functions */
#define  DEVICE_MODE_ISDBT 138 
#define  DEVICE_MODE_ISDBT_BDA 137 
 int /*<<< orphan*/  DVB3_EVENT_FE_LOCK ; 
 int /*<<< orphan*/  DVB3_EVENT_FE_UNLOCK ; 
 int /*<<< orphan*/  DVB3_EVENT_UNC_ERR ; 
 int /*<<< orphan*/  DVB3_EVENT_UNC_OK ; 
 int FE_HAS_CARRIER ; 
 int FE_HAS_LOCK ; 
 int FE_HAS_SIGNAL ; 
 int FE_HAS_SYNC ; 
 int FE_HAS_VITERBI ; 
#define  MSG_SMS_DVBT_BDA_DATA 136 
#define  MSG_SMS_GET_STATISTICS_EX_RES 135 
#define  MSG_SMS_GET_STATISTICS_RES 134 
#define  MSG_SMS_HO_PER_SLICES_IND 133 
#define  MSG_SMS_ISDBT_TUNE_RES 132 
#define  MSG_SMS_NO_SIGNAL_IND 131 
#define  MSG_SMS_RF_TUNE_RES 130 
#define  MSG_SMS_SIGNAL_DETECTED_IND 129 
#define  MSG_SMS_TRANSMISSION_IND 128 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_dmx_swfilter (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  sms_board_dvb3_event (struct smsdvb_client_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smscore_get_device_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smscore_putbuffer (int /*<<< orphan*/ ,struct smscore_buffer_t*) ; 
 int /*<<< orphan*/  smsdvb_stats_not_ready (struct dvb_frontend*) ; 
 int /*<<< orphan*/  smsdvb_update_dvb_stats (struct smsdvb_client_t*,void*) ; 
 int /*<<< orphan*/  smsdvb_update_isdbt_stats (struct smsdvb_client_t*,void*) ; 
 int /*<<< orphan*/  smsdvb_update_isdbt_stats_ex (struct smsdvb_client_t*,void*) ; 
 int /*<<< orphan*/  smsdvb_update_per_slices (struct smsdvb_client_t*,void*) ; 
 int /*<<< orphan*/  smsdvb_update_tx_params (struct smsdvb_client_t*,void*) ; 

__attribute__((used)) static int smsdvb_onresponse(void *context, struct smscore_buffer_t *cb)
{
	struct smsdvb_client_t *client = (struct smsdvb_client_t *) context;
	struct sms_msg_hdr *phdr = (struct sms_msg_hdr *) (((u8 *) cb->p)
			+ cb->offset);
	void *p = phdr + 1;
	struct dvb_frontend *fe = &client->frontend;
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;
	bool is_status_update = false;

	switch (phdr->msg_type) {
	case MSG_SMS_DVBT_BDA_DATA:
		/*
		 * Only feed data to dvb demux if are there any feed listening
		 * to it and if the device has tuned
		 */
		if (client->feed_users && client->has_tuned)
			dvb_dmx_swfilter(&client->demux, p,
					 cb->size - sizeof(struct sms_msg_hdr));
		break;

	case MSG_SMS_RF_TUNE_RES:
	case MSG_SMS_ISDBT_TUNE_RES:
		complete(&client->tune_done);
		break;

	case MSG_SMS_SIGNAL_DETECTED_IND:
		client->fe_status = FE_HAS_SIGNAL  | FE_HAS_CARRIER |
				    FE_HAS_VITERBI | FE_HAS_SYNC    |
				    FE_HAS_LOCK;

		is_status_update = true;
		break;

	case MSG_SMS_NO_SIGNAL_IND:
		client->fe_status = 0;

		is_status_update = true;
		break;

	case MSG_SMS_TRANSMISSION_IND:
		smsdvb_update_tx_params(client, p);

		is_status_update = true;
		break;

	case MSG_SMS_HO_PER_SLICES_IND:
		smsdvb_update_per_slices(client, p);

		is_status_update = true;
		break;

	case MSG_SMS_GET_STATISTICS_RES:
		switch (smscore_get_device_mode(client->coredev)) {
		case DEVICE_MODE_ISDBT:
		case DEVICE_MODE_ISDBT_BDA:
			smsdvb_update_isdbt_stats(client, p);
			break;
		default:
			/* Skip sms_msg_statistics_info:request_result field */
			smsdvb_update_dvb_stats(client, p + sizeof(u32));
		}

		is_status_update = true;
		break;

	/* Only for ISDB-T */
	case MSG_SMS_GET_STATISTICS_EX_RES:
		/* Skip sms_msg_statistics_info:request_result field? */
		smsdvb_update_isdbt_stats_ex(client, p + sizeof(u32));
		is_status_update = true;
		break;
	default:
		pr_debug("message not handled\n");
	}
	smscore_putbuffer(client->coredev, cb);

	if (is_status_update) {
		if (client->fe_status & FE_HAS_LOCK) {
			sms_board_dvb3_event(client, DVB3_EVENT_FE_LOCK);
			if (client->last_per == c->block_error.stat[0].uvalue)
				sms_board_dvb3_event(client, DVB3_EVENT_UNC_OK);
			else
				sms_board_dvb3_event(client, DVB3_EVENT_UNC_ERR);
			client->has_tuned = true;
		} else {
			smsdvb_stats_not_ready(fe);
			client->has_tuned = false;
			sms_board_dvb3_event(client, DVB3_EVENT_FE_UNLOCK);
		}
		complete(&client->stats_done);
	}

	return 0;
}