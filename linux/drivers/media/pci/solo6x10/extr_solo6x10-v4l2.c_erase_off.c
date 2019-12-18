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
struct solo_dev {scalar_t__ erasing; int /*<<< orphan*/  frame_blank; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOLO_VO_DISP_ERASE ; 
 int /*<<< orphan*/  solo_reg_write (struct solo_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int erase_off(struct solo_dev *solo_dev)
{
	if (!solo_dev->erasing)
		return 0;

	/* First time around, assert erase off */
	if (!solo_dev->frame_blank)
		solo_reg_write(solo_dev, SOLO_VO_DISP_ERASE, 0);
	/* Keep the erasing flag on for 8 frames minimum */
	if (solo_dev->frame_blank++ >= 8)
		solo_dev->erasing = 0;

	return 1;
}