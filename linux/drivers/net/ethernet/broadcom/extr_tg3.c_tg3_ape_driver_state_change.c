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
typedef  int u32 ;
struct tg3 {TYPE_1__* pdev; int /*<<< orphan*/  ape_hb; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int APE_EVENT_STATUS_DRIVER_EVNT ; 
 int APE_EVENT_STATUS_STATE_CHNGE ; 
 int APE_EVENT_STATUS_STATE_START ; 
 int APE_EVENT_STATUS_STATE_UNLOAD ; 
 int APE_HOST_BEHAV_NO_PHYLOCK ; 
 int APE_HOST_DRIVER_ID_MAGIC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int APE_HOST_SEG_LEN_MAGIC ; 
 int APE_HOST_SEG_SIG_MAGIC ; 
 int /*<<< orphan*/  ENABLE_APE ; 
#define  RESET_KIND_INIT 129 
#define  RESET_KIND_SHUTDOWN 128 
 int /*<<< orphan*/  TG3_APE_HOST_BEHAVIOR ; 
 int /*<<< orphan*/  TG3_APE_HOST_DRIVER_ID ; 
 int /*<<< orphan*/  TG3_APE_HOST_DRVR_STATE ; 
 int TG3_APE_HOST_DRVR_STATE_START ; 
 int TG3_APE_HOST_DRVR_STATE_UNLOAD ; 
 int TG3_APE_HOST_DRVR_STATE_WOL ; 
 int /*<<< orphan*/  TG3_APE_HOST_HEARTBEAT_COUNT ; 
 int /*<<< orphan*/  TG3_APE_HOST_INIT_COUNT ; 
 int /*<<< orphan*/  TG3_APE_HOST_SEG_LEN ; 
 int /*<<< orphan*/  TG3_APE_HOST_SEG_SIG ; 
 int /*<<< orphan*/  TG3_APE_HOST_WOL_SPEED ; 
 int TG3_APE_HOST_WOL_SPEED_AUTO ; 
 int /*<<< orphan*/  TG3_MAJ_NUM ; 
 int /*<<< orphan*/  TG3_MIN_NUM ; 
 int /*<<< orphan*/  WOL_ENABLE ; 
 int /*<<< orphan*/  device_may_wakeup (int /*<<< orphan*/ *) ; 
 int tg3_ape_read32 (struct tg3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tg3_ape_send_event (struct tg3*,int) ; 
 int /*<<< orphan*/  tg3_ape_write32 (struct tg3*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ tg3_flag (struct tg3*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tg3_ape_driver_state_change(struct tg3 *tp, int kind)
{
	u32 event;
	u32 apedata;

	if (!tg3_flag(tp, ENABLE_APE))
		return;

	switch (kind) {
	case RESET_KIND_INIT:
		tg3_ape_write32(tp, TG3_APE_HOST_HEARTBEAT_COUNT, tp->ape_hb++);
		tg3_ape_write32(tp, TG3_APE_HOST_SEG_SIG,
				APE_HOST_SEG_SIG_MAGIC);
		tg3_ape_write32(tp, TG3_APE_HOST_SEG_LEN,
				APE_HOST_SEG_LEN_MAGIC);
		apedata = tg3_ape_read32(tp, TG3_APE_HOST_INIT_COUNT);
		tg3_ape_write32(tp, TG3_APE_HOST_INIT_COUNT, ++apedata);
		tg3_ape_write32(tp, TG3_APE_HOST_DRIVER_ID,
			APE_HOST_DRIVER_ID_MAGIC(TG3_MAJ_NUM, TG3_MIN_NUM));
		tg3_ape_write32(tp, TG3_APE_HOST_BEHAVIOR,
				APE_HOST_BEHAV_NO_PHYLOCK);
		tg3_ape_write32(tp, TG3_APE_HOST_DRVR_STATE,
				    TG3_APE_HOST_DRVR_STATE_START);

		event = APE_EVENT_STATUS_STATE_START;
		break;
	case RESET_KIND_SHUTDOWN:
		if (device_may_wakeup(&tp->pdev->dev) &&
		    tg3_flag(tp, WOL_ENABLE)) {
			tg3_ape_write32(tp, TG3_APE_HOST_WOL_SPEED,
					    TG3_APE_HOST_WOL_SPEED_AUTO);
			apedata = TG3_APE_HOST_DRVR_STATE_WOL;
		} else
			apedata = TG3_APE_HOST_DRVR_STATE_UNLOAD;

		tg3_ape_write32(tp, TG3_APE_HOST_DRVR_STATE, apedata);

		event = APE_EVENT_STATUS_STATE_UNLOAD;
		break;
	default:
		return;
	}

	event |= APE_EVENT_STATUS_DRIVER_EVNT | APE_EVENT_STATUS_STATE_CHNGE;

	tg3_ape_send_event(tp, event);
}