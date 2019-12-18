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
struct TYPE_3__ {int bytype; int /*<<< orphan*/  bylength; } ;
struct TYPE_4__ {TYPE_1__ hdr; } ;
struct esas2r_vda_ae {TYPE_2__ vda_ae; } ;
struct esas2r_fw_event_work {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESAS2R_LOG_WARN ; 
#define  VDAAE_HDR_TYPE_DEV 142 
#define  VDAAE_HDR_TYPE_DISK 141 
#define  VDAAE_HDR_TYPE_LOG_CRIT 140 
#define  VDAAE_HDR_TYPE_LOG_FAIL 139 
#define  VDAAE_HDR_TYPE_LOG_INFO 138 
#define  VDAAE_HDR_TYPE_LOG_WARN 137 
#define  VDAAE_HDR_TYPE_LU 136 
#define  VDAAE_HDR_TYPE_MUTE 135 
#define  VDAAE_HDR_TYPE_NVC 134 
#define  VDAAE_HDR_TYPE_PWRMGT 133 
#define  VDAAE_HDR_TYPE_RAID 132 
#define  VDAAE_HDR_TYPE_RESET 131 
#define  VDAAE_HDR_TYPE_TLG_CRIT 130 
#define  VDAAE_HDR_TYPE_TLG_INFO 129 
#define  VDAAE_HDR_TYPE_TLG_WARN 128 
 int /*<<< orphan*/  esas2r_log (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  esas2r_log_hexdump (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void esas2r_send_ae_event(struct esas2r_fw_event_work *fw_event)
{
	struct esas2r_vda_ae *ae = (struct esas2r_vda_ae *)fw_event->data;
	char *type;

	switch (ae->vda_ae.hdr.bytype) {
	case VDAAE_HDR_TYPE_RAID:
		type = "RAID group state change";
		break;

	case VDAAE_HDR_TYPE_LU:
		type = "Mapped destination LU change";
		break;

	case VDAAE_HDR_TYPE_DISK:
		type = "Physical disk inventory change";
		break;

	case VDAAE_HDR_TYPE_RESET:
		type = "Firmware reset";
		break;

	case VDAAE_HDR_TYPE_LOG_INFO:
		type = "Event Log message (INFO level)";
		break;

	case VDAAE_HDR_TYPE_LOG_WARN:
		type = "Event Log message (WARN level)";
		break;

	case VDAAE_HDR_TYPE_LOG_CRIT:
		type = "Event Log message (CRIT level)";
		break;

	case VDAAE_HDR_TYPE_LOG_FAIL:
		type = "Event Log message (FAIL level)";
		break;

	case VDAAE_HDR_TYPE_NVC:
		type = "NVCache change";
		break;

	case VDAAE_HDR_TYPE_TLG_INFO:
		type = "Time stamped log message (INFO level)";
		break;

	case VDAAE_HDR_TYPE_TLG_WARN:
		type = "Time stamped log message (WARN level)";
		break;

	case VDAAE_HDR_TYPE_TLG_CRIT:
		type = "Time stamped log message (CRIT level)";
		break;

	case VDAAE_HDR_TYPE_PWRMGT:
		type = "Power management";
		break;

	case VDAAE_HDR_TYPE_MUTE:
		type = "Mute button pressed";
		break;

	case VDAAE_HDR_TYPE_DEV:
		type = "Device attribute change";
		break;

	default:
		type = "Unknown";
		break;
	}

	esas2r_log(ESAS2R_LOG_WARN,
		   "An async event of type \"%s\" was received from the firmware.  The event contents are:",
		   type);
	esas2r_log_hexdump(ESAS2R_LOG_WARN, &ae->vda_ae,
			   ae->vda_ae.hdr.bylength);

}