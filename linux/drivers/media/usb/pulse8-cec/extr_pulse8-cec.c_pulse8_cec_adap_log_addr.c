#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct pulse8 {int restoring_config; int autonomous; int config_pending; int /*<<< orphan*/  config_lock; } ;
struct TYPE_2__ {int* primary_device_type; int cec_version; char* osd_name; } ;
struct cec_adapter {int phys_addr; TYPE_1__ log_addrs; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int CEC_LOG_ADDR_INVALID ; 
 int CEC_LOG_ADDR_MASK_AUDIOSYSTEM ; 
 int CEC_LOG_ADDR_MASK_PLAYBACK ; 
 int CEC_LOG_ADDR_MASK_RECORD ; 
 int CEC_LOG_ADDR_MASK_SPECIFIC ; 
 int CEC_LOG_ADDR_MASK_TUNER ; 
 int CEC_LOG_ADDR_MASK_TV ; 
 int CEC_LOG_ADDR_MASK_UNREGISTERED ; 
#define  CEC_OP_PRIM_DEVTYPE_AUDIOSYSTEM 134 
#define  CEC_OP_PRIM_DEVTYPE_PLAYBACK 133 
#define  CEC_OP_PRIM_DEVTYPE_PROCESSOR 132 
#define  CEC_OP_PRIM_DEVTYPE_RECORD 131 
#define  CEC_OP_PRIM_DEVTYPE_SWITCH 130 
#define  CEC_OP_PRIM_DEVTYPE_TUNER 129 
#define  CEC_OP_PRIM_DEVTYPE_TV 128 
 int /*<<< orphan*/  MSGCODE_COMMAND_ACCEPTED ; 
 int MSGCODE_SET_ACK_MASK ; 
 int MSGCODE_SET_AUTO_ENABLED ; 
 int MSGCODE_SET_DEFAULT_LOGICAL_ADDRESS ; 
 int MSGCODE_SET_DEVICE_TYPE ; 
 int MSGCODE_SET_HDMI_VERSION ; 
 int MSGCODE_SET_LOGICAL_ADDRESS_MASK ; 
 int MSGCODE_SET_OSD_NAME ; 
 int MSGCODE_SET_PHYSICAL_ADDRESS ; 
 struct pulse8* cec_get_drvdata (struct cec_adapter*) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pulse8_send_and_wait (struct pulse8*,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  strscpy (int*,char*,int) ; 

__attribute__((used)) static int pulse8_cec_adap_log_addr(struct cec_adapter *adap, u8 log_addr)
{
	struct pulse8 *pulse8 = cec_get_drvdata(adap);
	u16 mask = 0;
	u16 pa = adap->phys_addr;
	u8 cmd[16];
	int err = 0;

	mutex_lock(&pulse8->config_lock);
	if (log_addr != CEC_LOG_ADDR_INVALID)
		mask = 1 << log_addr;
	cmd[0] = MSGCODE_SET_ACK_MASK;
	cmd[1] = mask >> 8;
	cmd[2] = mask & 0xff;
	err = pulse8_send_and_wait(pulse8, cmd, 3,
				   MSGCODE_COMMAND_ACCEPTED, 0);
	if ((err && mask != 0) || pulse8->restoring_config)
		goto unlock;

	cmd[0] = MSGCODE_SET_AUTO_ENABLED;
	cmd[1] = log_addr == CEC_LOG_ADDR_INVALID ? 0 : 1;
	err = pulse8_send_and_wait(pulse8, cmd, 2,
				   MSGCODE_COMMAND_ACCEPTED, 0);
	if (err)
		goto unlock;
	pulse8->autonomous = cmd[1];
	if (log_addr == CEC_LOG_ADDR_INVALID)
		goto unlock;

	cmd[0] = MSGCODE_SET_DEVICE_TYPE;
	cmd[1] = adap->log_addrs.primary_device_type[0];
	err = pulse8_send_and_wait(pulse8, cmd, 2,
				   MSGCODE_COMMAND_ACCEPTED, 0);
	if (err)
		goto unlock;

	switch (adap->log_addrs.primary_device_type[0]) {
	case CEC_OP_PRIM_DEVTYPE_TV:
		mask = CEC_LOG_ADDR_MASK_TV;
		break;
	case CEC_OP_PRIM_DEVTYPE_RECORD:
		mask = CEC_LOG_ADDR_MASK_RECORD;
		break;
	case CEC_OP_PRIM_DEVTYPE_TUNER:
		mask = CEC_LOG_ADDR_MASK_TUNER;
		break;
	case CEC_OP_PRIM_DEVTYPE_PLAYBACK:
		mask = CEC_LOG_ADDR_MASK_PLAYBACK;
		break;
	case CEC_OP_PRIM_DEVTYPE_AUDIOSYSTEM:
		mask = CEC_LOG_ADDR_MASK_AUDIOSYSTEM;
		break;
	case CEC_OP_PRIM_DEVTYPE_SWITCH:
		mask = CEC_LOG_ADDR_MASK_UNREGISTERED;
		break;
	case CEC_OP_PRIM_DEVTYPE_PROCESSOR:
		mask = CEC_LOG_ADDR_MASK_SPECIFIC;
		break;
	default:
		mask = 0;
		break;
	}
	cmd[0] = MSGCODE_SET_LOGICAL_ADDRESS_MASK;
	cmd[1] = mask >> 8;
	cmd[2] = mask & 0xff;
	err = pulse8_send_and_wait(pulse8, cmd, 3,
				   MSGCODE_COMMAND_ACCEPTED, 0);
	if (err)
		goto unlock;

	cmd[0] = MSGCODE_SET_DEFAULT_LOGICAL_ADDRESS;
	cmd[1] = log_addr;
	err = pulse8_send_and_wait(pulse8, cmd, 2,
				   MSGCODE_COMMAND_ACCEPTED, 0);
	if (err)
		goto unlock;

	cmd[0] = MSGCODE_SET_PHYSICAL_ADDRESS;
	cmd[1] = pa >> 8;
	cmd[2] = pa & 0xff;
	err = pulse8_send_and_wait(pulse8, cmd, 3,
				   MSGCODE_COMMAND_ACCEPTED, 0);
	if (err)
		goto unlock;

	cmd[0] = MSGCODE_SET_HDMI_VERSION;
	cmd[1] = adap->log_addrs.cec_version;
	err = pulse8_send_and_wait(pulse8, cmd, 2,
				   MSGCODE_COMMAND_ACCEPTED, 0);
	if (err)
		goto unlock;

	if (adap->log_addrs.osd_name[0]) {
		size_t osd_len = strlen(adap->log_addrs.osd_name);
		char *osd_str = cmd + 1;

		cmd[0] = MSGCODE_SET_OSD_NAME;
		strscpy(cmd + 1, adap->log_addrs.osd_name, sizeof(cmd) - 1);
		if (osd_len < 4) {
			memset(osd_str + osd_len, ' ', 4 - osd_len);
			osd_len = 4;
			osd_str[osd_len] = '\0';
			strscpy(adap->log_addrs.osd_name, osd_str,
				sizeof(adap->log_addrs.osd_name));
		}
		err = pulse8_send_and_wait(pulse8, cmd, 1 + osd_len,
					   MSGCODE_COMMAND_ACCEPTED, 0);
		if (err)
			goto unlock;
	}

unlock:
	if (pulse8->restoring_config)
		pulse8->restoring_config = false;
	else
		pulse8->config_pending = true;
	mutex_unlock(&pulse8->config_lock);
	return log_addr == CEC_LOG_ADDR_INVALID ? 0 : err;
}