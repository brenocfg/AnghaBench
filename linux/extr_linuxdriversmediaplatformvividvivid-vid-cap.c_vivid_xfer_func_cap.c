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
struct vivid_dev {int xfer_func_out; int /*<<< orphan*/  tpg; int /*<<< orphan*/  loop_video; } ;

/* Variables and functions */
 int tpg_g_xfer_func (int /*<<< orphan*/ *) ; 
 scalar_t__ vivid_is_tv_cap (struct vivid_dev*) ; 
 scalar_t__ vivid_is_webcam (struct vivid_dev*) ; 

__attribute__((used)) static unsigned vivid_xfer_func_cap(struct vivid_dev *dev)
{
	if (!dev->loop_video || vivid_is_webcam(dev) || vivid_is_tv_cap(dev))
		return tpg_g_xfer_func(&dev->tpg);
	return dev->xfer_func_out;
}