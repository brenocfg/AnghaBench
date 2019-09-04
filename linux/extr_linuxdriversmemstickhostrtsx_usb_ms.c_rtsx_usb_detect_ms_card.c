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
struct rtsx_usb_ms {int /*<<< orphan*/  detect_ms_exit; scalar_t__ eject; int /*<<< orphan*/  msh; struct rtsx_ucr* ucr; } ;
struct rtsx_ucr {int /*<<< orphan*/  dev_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_INT_PEND ; 
 int /*<<< orphan*/  HZ ; 
 int MS_INT ; 
 int SD_INT ; 
 int XD_INT ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memstick_detect_change (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ms_dev (struct rtsx_usb_ms*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int rtsx_usb_read_register (struct rtsx_ucr*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  rtsx_usb_write_register (struct rtsx_ucr*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  schedule_timeout_idle (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtsx_usb_detect_ms_card(void *__host)
{
	struct rtsx_usb_ms *host = (struct rtsx_usb_ms *)__host;
	struct rtsx_ucr *ucr = host->ucr;
	u8 val = 0;
	int err;

	for (;;) {
		pm_runtime_get_sync(ms_dev(host));
		mutex_lock(&ucr->dev_mutex);

		/* Check pending MS card changes */
		err = rtsx_usb_read_register(ucr, CARD_INT_PEND, &val);
		if (err) {
			mutex_unlock(&ucr->dev_mutex);
			goto poll_again;
		}

		/* Clear the pending */
		rtsx_usb_write_register(ucr, CARD_INT_PEND,
				XD_INT | MS_INT | SD_INT,
				XD_INT | MS_INT | SD_INT);

		mutex_unlock(&ucr->dev_mutex);

		if (val & MS_INT) {
			dev_dbg(ms_dev(host), "MS slot change detected\n");
			memstick_detect_change(host->msh);
		}

poll_again:
		pm_runtime_put(ms_dev(host));
		if (host->eject)
			break;

		schedule_timeout_idle(HZ);
	}

	complete(&host->detect_ms_exit);
	return 0;
}