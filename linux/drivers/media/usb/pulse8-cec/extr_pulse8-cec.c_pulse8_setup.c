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
typedef  int u8 ;
typedef  int u16 ;
typedef  int time64_t ;
struct tm {int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_mday; scalar_t__ tm_mon; scalar_t__ tm_year; } ;
struct serio {int dummy; } ;
struct pulse8 {int* data; int vers; int autonomous; int /*<<< orphan*/  dev; } ;
struct cec_log_addrs {int* primary_device_type; int log_addr_mask; int num_log_addrs; int cec_version; int osd_name; void** all_device_types; void** log_addr_type; } ;

/* Variables and functions */
 void* CEC_LOG_ADDR_TYPE_PLAYBACK ; 
 void* CEC_LOG_ADDR_TYPE_RECORD ; 
 void* CEC_LOG_ADDR_TYPE_SPECIFIC ; 
 void* CEC_LOG_ADDR_TYPE_TUNER ; 
 void* CEC_LOG_ADDR_TYPE_TV ; 
 void* CEC_LOG_ADDR_TYPE_UNREGISTERED ; 
 void* CEC_OP_ALL_DEVTYPE_AUDIOSYSTEM ; 
 void* CEC_OP_ALL_DEVTYPE_PLAYBACK ; 
 void* CEC_OP_ALL_DEVTYPE_RECORD ; 
 void* CEC_OP_ALL_DEVTYPE_SWITCH ; 
 void* CEC_OP_ALL_DEVTYPE_TUNER ; 
 void* CEC_OP_ALL_DEVTYPE_TV ; 
#define  CEC_OP_PRIM_DEVTYPE_AUDIOSYSTEM 134 
#define  CEC_OP_PRIM_DEVTYPE_PLAYBACK 133 
#define  CEC_OP_PRIM_DEVTYPE_PROCESSOR 132 
#define  CEC_OP_PRIM_DEVTYPE_RECORD 131 
#define  CEC_OP_PRIM_DEVTYPE_SWITCH 130 
#define  CEC_OP_PRIM_DEVTYPE_TUNER 129 
#define  CEC_OP_PRIM_DEVTYPE_TV 128 
 int CEC_PHYS_ADDR_INVALID ; 
 int MSGCODE_FIRMWARE_VERSION ; 
 int MSGCODE_GET_AUTO_ENABLED ; 
 int MSGCODE_GET_BUILDDATE ; 
 int MSGCODE_GET_DEVICE_TYPE ; 
 int MSGCODE_GET_HDMI_VERSION ; 
 int MSGCODE_GET_LOGICAL_ADDRESS_MASK ; 
 int MSGCODE_GET_OSD_NAME ; 
 int MSGCODE_GET_PHYSICAL_ADDRESS ; 
 int cec_phys_addr_exp (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int,...) ; 
 int pulse8_send_and_wait (struct pulse8*,int*,int,int,int) ; 
 int /*<<< orphan*/  strscpy (int,int*,int) ; 
 int /*<<< orphan*/  time64_to_tm (int,int /*<<< orphan*/ ,struct tm*) ; 

__attribute__((used)) static int pulse8_setup(struct pulse8 *pulse8, struct serio *serio,
			struct cec_log_addrs *log_addrs, u16 *pa)
{
	u8 *data = pulse8->data + 1;
	u8 cmd[2];
	int err;
	struct tm tm;
	time64_t date;

	pulse8->vers = 0;

	cmd[0] = MSGCODE_FIRMWARE_VERSION;
	err = pulse8_send_and_wait(pulse8, cmd, 1, cmd[0], 2);
	if (err)
		return err;
	pulse8->vers = (data[0] << 8) | data[1];
	dev_info(pulse8->dev, "Firmware version %04x\n", pulse8->vers);
	if (pulse8->vers < 2) {
		*pa = CEC_PHYS_ADDR_INVALID;
		return 0;
	}

	cmd[0] = MSGCODE_GET_BUILDDATE;
	err = pulse8_send_and_wait(pulse8, cmd, 1, cmd[0], 4);
	if (err)
		return err;
	date = (data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3];
	time64_to_tm(date, 0, &tm);
	dev_info(pulse8->dev, "Firmware build date %04ld.%02d.%02d %02d:%02d:%02d\n",
		 tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
		 tm.tm_hour, tm.tm_min, tm.tm_sec);

	dev_dbg(pulse8->dev, "Persistent config:\n");
	cmd[0] = MSGCODE_GET_AUTO_ENABLED;
	err = pulse8_send_and_wait(pulse8, cmd, 1, cmd[0], 1);
	if (err)
		return err;
	pulse8->autonomous = data[0];
	dev_dbg(pulse8->dev, "Autonomous mode: %s",
		data[0] ? "on" : "off");

	cmd[0] = MSGCODE_GET_DEVICE_TYPE;
	err = pulse8_send_and_wait(pulse8, cmd, 1, cmd[0], 1);
	if (err)
		return err;
	log_addrs->primary_device_type[0] = data[0];
	dev_dbg(pulse8->dev, "Primary device type: %d\n", data[0]);
	switch (log_addrs->primary_device_type[0]) {
	case CEC_OP_PRIM_DEVTYPE_TV:
		log_addrs->log_addr_type[0] = CEC_LOG_ADDR_TYPE_TV;
		log_addrs->all_device_types[0] = CEC_OP_ALL_DEVTYPE_TV;
		break;
	case CEC_OP_PRIM_DEVTYPE_RECORD:
		log_addrs->log_addr_type[0] = CEC_LOG_ADDR_TYPE_RECORD;
		log_addrs->all_device_types[0] = CEC_OP_ALL_DEVTYPE_RECORD;
		break;
	case CEC_OP_PRIM_DEVTYPE_TUNER:
		log_addrs->log_addr_type[0] = CEC_LOG_ADDR_TYPE_TUNER;
		log_addrs->all_device_types[0] = CEC_OP_ALL_DEVTYPE_TUNER;
		break;
	case CEC_OP_PRIM_DEVTYPE_PLAYBACK:
		log_addrs->log_addr_type[0] = CEC_LOG_ADDR_TYPE_PLAYBACK;
		log_addrs->all_device_types[0] = CEC_OP_ALL_DEVTYPE_PLAYBACK;
		break;
	case CEC_OP_PRIM_DEVTYPE_AUDIOSYSTEM:
		log_addrs->log_addr_type[0] = CEC_LOG_ADDR_TYPE_PLAYBACK;
		log_addrs->all_device_types[0] = CEC_OP_ALL_DEVTYPE_AUDIOSYSTEM;
		break;
	case CEC_OP_PRIM_DEVTYPE_SWITCH:
		log_addrs->log_addr_type[0] = CEC_LOG_ADDR_TYPE_UNREGISTERED;
		log_addrs->all_device_types[0] = CEC_OP_ALL_DEVTYPE_SWITCH;
		break;
	case CEC_OP_PRIM_DEVTYPE_PROCESSOR:
		log_addrs->log_addr_type[0] = CEC_LOG_ADDR_TYPE_SPECIFIC;
		log_addrs->all_device_types[0] = CEC_OP_ALL_DEVTYPE_SWITCH;
		break;
	default:
		log_addrs->log_addr_type[0] = CEC_LOG_ADDR_TYPE_UNREGISTERED;
		log_addrs->all_device_types[0] = CEC_OP_ALL_DEVTYPE_SWITCH;
		dev_info(pulse8->dev, "Unknown Primary Device Type: %d\n",
			 log_addrs->primary_device_type[0]);
		break;
	}

	cmd[0] = MSGCODE_GET_LOGICAL_ADDRESS_MASK;
	err = pulse8_send_and_wait(pulse8, cmd, 1, cmd[0], 2);
	if (err)
		return err;
	log_addrs->log_addr_mask = (data[0] << 8) | data[1];
	dev_dbg(pulse8->dev, "Logical address ACK mask: %x\n",
		log_addrs->log_addr_mask);
	if (log_addrs->log_addr_mask)
		log_addrs->num_log_addrs = 1;

	cmd[0] = MSGCODE_GET_PHYSICAL_ADDRESS;
	err = pulse8_send_and_wait(pulse8, cmd, 1, cmd[0], 1);
	if (err)
		return err;
	*pa = (data[0] << 8) | data[1];
	dev_dbg(pulse8->dev, "Physical address: %x.%x.%x.%x\n",
		cec_phys_addr_exp(*pa));

	cmd[0] = MSGCODE_GET_HDMI_VERSION;
	err = pulse8_send_and_wait(pulse8, cmd, 1, cmd[0], 1);
	if (err)
		return err;
	log_addrs->cec_version = data[0];
	dev_dbg(pulse8->dev, "CEC version: %d\n", log_addrs->cec_version);

	cmd[0] = MSGCODE_GET_OSD_NAME;
	err = pulse8_send_and_wait(pulse8, cmd, 1, cmd[0], 0);
	if (err)
		return err;
	strscpy(log_addrs->osd_name, data, sizeof(log_addrs->osd_name));
	dev_dbg(pulse8->dev, "OSD name: %s\n", log_addrs->osd_name);

	return 0;
}