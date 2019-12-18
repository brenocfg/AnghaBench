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
struct fmdev {int /*<<< orphan*/  curr_fmmode; int /*<<< orphan*/  flag; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  FM_CORE_READY ; 
 int /*<<< orphan*/  fmerr (char*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int fmc_get_mode(struct fmdev *fmdev, u8 *fmmode)
{
	if (!test_bit(FM_CORE_READY, &fmdev->flag)) {
		fmerr("FM core is not ready\n");
		return -EPERM;
	}
	if (fmmode == NULL) {
		fmerr("Invalid memory\n");
		return -ENOMEM;
	}

	*fmmode = fmdev->curr_fmmode;
	return 0;
}