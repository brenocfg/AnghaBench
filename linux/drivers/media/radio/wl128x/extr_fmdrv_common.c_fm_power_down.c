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
typedef  int u16 ;
struct fmdev {scalar_t__ curr_fmmode; int /*<<< orphan*/  flag; } ;
typedef  int /*<<< orphan*/  payload ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  FM_CORE_READY ; 
 scalar_t__ FM_MODE_OFF ; 
 int /*<<< orphan*/  FM_POWER_MODE ; 
 int /*<<< orphan*/  REG_WR ; 
 int fmc_release (struct fmdev*) ; 
 int fmc_send_cmd (struct fmdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fmdbg (char*) ; 
 int /*<<< orphan*/  fmerr (char*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fm_power_down(struct fmdev *fmdev)
{
	u16 payload;
	int ret;

	if (!test_bit(FM_CORE_READY, &fmdev->flag)) {
		fmerr("FM core is not ready\n");
		return -EPERM;
	}
	if (fmdev->curr_fmmode == FM_MODE_OFF) {
		fmdbg("FM chip is already in OFF state\n");
		return 0;
	}

	payload = 0x0;
	ret = fmc_send_cmd(fmdev, FM_POWER_MODE, REG_WR, &payload,
		sizeof(payload), NULL, NULL);
	if (ret < 0)
		return ret;

	return fmc_release(fmdev);
}