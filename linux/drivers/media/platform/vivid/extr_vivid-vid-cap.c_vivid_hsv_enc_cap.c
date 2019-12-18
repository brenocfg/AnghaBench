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
struct vivid_dev {unsigned int hsv_enc_out; int /*<<< orphan*/  tpg; int /*<<< orphan*/  loop_video; } ;

/* Variables and functions */
 unsigned int tpg_g_hsv_enc (int /*<<< orphan*/ *) ; 
 scalar_t__ vivid_is_tv_cap (struct vivid_dev*) ; 
 scalar_t__ vivid_is_webcam (struct vivid_dev*) ; 

__attribute__((used)) static unsigned int vivid_hsv_enc_cap(struct vivid_dev *dev)
{
	if (!dev->loop_video || vivid_is_webcam(dev) || vivid_is_tv_cap(dev))
		return tpg_g_hsv_enc(&dev->tpg);
	return dev->hsv_enc_out;
}