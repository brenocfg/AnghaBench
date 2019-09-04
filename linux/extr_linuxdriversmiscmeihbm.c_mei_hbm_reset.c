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
struct mei_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mei_hbm_idle (struct mei_device*) ; 
 int /*<<< orphan*/  mei_me_cl_rm_all (struct mei_device*) ; 

void mei_hbm_reset(struct mei_device *dev)
{
	mei_me_cl_rm_all(dev);

	mei_hbm_idle(dev);
}