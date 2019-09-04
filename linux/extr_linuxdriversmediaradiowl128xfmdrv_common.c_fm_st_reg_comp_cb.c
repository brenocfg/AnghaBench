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
struct fmdev {int streg_cbdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_fmdrv_reg_comp ; 

__attribute__((used)) static void fm_st_reg_comp_cb(void *arg, int data)
{
	struct fmdev *fmdev;

	fmdev = (struct fmdev *)arg;
	fmdev->streg_cbdata = data;
	complete(&wait_for_fmdrv_reg_comp);
}