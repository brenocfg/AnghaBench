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
struct usb_chg_measures {int /*<<< orphan*/  current_max; int /*<<< orphan*/  voltage_max; int /*<<< orphan*/  voltage_now; } ;
struct rtc_time {int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_mday; scalar_t__ tm_mon; scalar_t__ tm_year; } ;
struct TYPE_4__ {int /*<<< orphan*/  build; int /*<<< orphan*/  minor; int /*<<< orphan*/  major; } ;
struct TYPE_3__ {int /*<<< orphan*/  build; int /*<<< orphan*/  minor; int /*<<< orphan*/  major; } ;
struct mcdp_info {TYPE_2__ fw; TYPE_1__ irom; int /*<<< orphan*/  chipid; int /*<<< orphan*/  family; } ;
struct ec_response_pd_log {int timestamp; int type; int data; int /*<<< orphan*/  size_port; int /*<<< orphan*/ * payload; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int ARRAY_SIZE (char**) ; 
 int /*<<< orphan*/  BUF_SIZE ; 
 int CHARGE_FLAGS_DELAYED_OVERRIDE ; 
 int CHARGE_FLAGS_DUAL_ROLE ; 
 int CHARGE_FLAGS_OVERRIDE ; 
 int CHARGE_FLAGS_ROLE_MASK ; 
 int CHARGE_FLAGS_TYPE_MASK ; 
 int CHARGE_FLAGS_TYPE_SHIFT ; 
 int /*<<< orphan*/  MCDP_CHIPID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MCDP_FAMILY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSEC_PER_SEC ; 
#define  PD_EVENT_ACC_RW_FAIL 132 
#define  PD_EVENT_MCU_CHARGE 131 
#define  PD_EVENT_PS_FAULT 130 
#define  PD_EVENT_VIDEO_CODEC 129 
#define  PD_EVENT_VIDEO_DP_MODE 128 
 int /*<<< orphan*/  PD_LOG_PORT (int /*<<< orphan*/ ) ; 
 int PD_LOG_SIZE (int /*<<< orphan*/ ) ; 
 int PD_LOG_TIMESTAMP_SHIFT ; 
 int USB_PD_PORT_POWER_DISCONNECTED ; 
 int USB_PD_PORT_POWER_SOURCE ; 
 int append_str (char*,int,char*,...) ; 
 char** chg_type_names ; 
 int /*<<< orphan*/  div_s64_rem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char** fault_names ; 
 int /*<<< orphan*/  ktime_sub_us (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ktime_to_ms (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 char** role_names ; 
 struct rtc_time rtc_ktime_to_tm (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cros_usbpd_print_log_entry(struct ec_response_pd_log *r,
				       ktime_t tstamp)
{
	const char *fault, *role, *chg_type;
	struct usb_chg_measures *meas;
	struct mcdp_info *minfo;
	int role_idx, type_idx;
	char buf[BUF_SIZE + 1];
	struct rtc_time rt;
	int len = 0;
	s32 rem;
	int i;

	/* The timestamp is the number of 1024th of seconds in the past */
	tstamp = ktime_sub_us(tstamp, r->timestamp << PD_LOG_TIMESTAMP_SHIFT);
	rt = rtc_ktime_to_tm(tstamp);

	switch (r->type) {
	case PD_EVENT_MCU_CHARGE:
		if (r->data & CHARGE_FLAGS_OVERRIDE)
			len += append_str(buf, len, "override ");

		if (r->data & CHARGE_FLAGS_DELAYED_OVERRIDE)
			len += append_str(buf, len, "pending_override ");

		role_idx = r->data & CHARGE_FLAGS_ROLE_MASK;
		role = role_idx < ARRAY_SIZE(role_names) ?
			role_names[role_idx] : "Unknown";

		type_idx = (r->data & CHARGE_FLAGS_TYPE_MASK)
			 >> CHARGE_FLAGS_TYPE_SHIFT;

		chg_type = type_idx < ARRAY_SIZE(chg_type_names) ?
			chg_type_names[type_idx] : "???";

		if (role_idx == USB_PD_PORT_POWER_DISCONNECTED ||
		    role_idx == USB_PD_PORT_POWER_SOURCE) {
			len += append_str(buf, len, "%s", role);
			break;
		}

		meas = (struct usb_chg_measures *)r->payload;
		len += append_str(buf, len, "%s %s %s %dmV max %dmV / %dmA",
				  role,	r->data & CHARGE_FLAGS_DUAL_ROLE ?
				  "DRP" : "Charger",
				  chg_type, meas->voltage_now,
				  meas->voltage_max, meas->current_max);
		break;
	case PD_EVENT_ACC_RW_FAIL:
		len += append_str(buf, len, "RW signature check failed");
		break;
	case PD_EVENT_PS_FAULT:
		fault = r->data < ARRAY_SIZE(fault_names) ? fault_names[r->data]
							  : "???";
		len += append_str(buf, len, "Power supply fault: %s", fault);
		break;
	case PD_EVENT_VIDEO_DP_MODE:
		len += append_str(buf, len, "DP mode %sabled", r->data == 1 ?
				  "en" : "dis");
		break;
	case PD_EVENT_VIDEO_CODEC:
		minfo = (struct mcdp_info *)r->payload;
		len += append_str(buf, len, "HDMI info: family:%04x chipid:%04x ",
				  MCDP_FAMILY(minfo->family),
				  MCDP_CHIPID(minfo->chipid));
		len += append_str(buf, len, "irom:%d.%d.%d fw:%d.%d.%d",
				  minfo->irom.major, minfo->irom.minor,
				  minfo->irom.build, minfo->fw.major,
				  minfo->fw.minor, minfo->fw.build);
		break;
	default:
		len += append_str(buf, len, "Event %02x (%04x) [", r->type,
				  r->data);

		for (i = 0; i < PD_LOG_SIZE(r->size_port); i++)
			len += append_str(buf, len, "%02x ", r->payload[i]);

		len += append_str(buf, len, "]");
		break;
	}

	div_s64_rem(ktime_to_ms(tstamp), MSEC_PER_SEC, &rem);
	pr_info("PDLOG %d/%02d/%02d %02d:%02d:%02d.%03d P%d %s\n",
		rt.tm_year + 1900, rt.tm_mon + 1, rt.tm_mday,
		rt.tm_hour, rt.tm_min, rt.tm_sec, rem,
		PD_LOG_PORT(r->size_port), buf);
}