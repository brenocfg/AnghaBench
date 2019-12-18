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
typedef  int /*<<< orphan*/  u16 ;
struct solo_dev {int nr_chans; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SOLO_MOT_FLAG_AREA ; 
 int SOLO_MOT_THRESH_SIZE ; 
 int solo_dma_vin_region (struct solo_dev*,scalar_t__,int /*<<< orphan*/ ,int) ; 

int solo_set_motion_threshold(struct solo_dev *solo_dev, u8 ch, u16 val)
{
	if (ch > solo_dev->nr_chans)
		return -EINVAL;

	return solo_dma_vin_region(solo_dev, SOLO_MOT_FLAG_AREA +
				   (ch * SOLO_MOT_THRESH_SIZE * 2),
				   val, SOLO_MOT_THRESH_SIZE);
}