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
typedef  scalar_t__ u8 ;
struct solo_dev {scalar_t__ nr_chans; scalar_t__ nr_ext; scalar_t__ cur_disp_ch; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  erase_on (struct solo_dev*) ; 
 int /*<<< orphan*/  solo_v4l2_ch (struct solo_dev*,scalar_t__,int) ; 

__attribute__((used)) static int solo_v4l2_set_ch(struct solo_dev *solo_dev, u8 ch)
{
	if (ch >= solo_dev->nr_chans + solo_dev->nr_ext)
		return -EINVAL;

	erase_on(solo_dev);

	solo_v4l2_ch(solo_dev, solo_dev->cur_disp_ch, 0);
	solo_v4l2_ch(solo_dev, ch, 1);

	solo_dev->cur_disp_ch = ch;

	return 0;
}