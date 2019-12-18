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
struct solo_dev {int erasing; scalar_t__ frame_blank; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOLO_VO_DISP_ERASE ; 
 int /*<<< orphan*/  SOLO_VO_DISP_ERASE_ON ; 
 int /*<<< orphan*/  solo_reg_write (struct solo_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void erase_on(struct solo_dev *solo_dev)
{
	solo_reg_write(solo_dev, SOLO_VO_DISP_ERASE, SOLO_VO_DISP_ERASE_ON);
	solo_dev->erasing = 1;
	solo_dev->frame_blank = 0;
}