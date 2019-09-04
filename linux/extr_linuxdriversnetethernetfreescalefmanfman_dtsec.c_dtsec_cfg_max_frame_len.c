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
typedef  int /*<<< orphan*/  u16 ;
struct fman_mac {TYPE_1__* dtsec_drv_param; } ;
struct TYPE_2__ {int /*<<< orphan*/  maximum_frame; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ is_init_done (TYPE_1__*) ; 

int dtsec_cfg_max_frame_len(struct fman_mac *dtsec, u16 new_val)
{
	if (is_init_done(dtsec->dtsec_drv_param))
		return -EINVAL;

	dtsec->dtsec_drv_param->maximum_frame = new_val;

	return 0;
}