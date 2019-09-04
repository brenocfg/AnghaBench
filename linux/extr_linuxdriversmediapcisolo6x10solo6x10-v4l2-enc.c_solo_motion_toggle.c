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
typedef  int u32 ;
struct solo_enc_dev {int ch; int /*<<< orphan*/  motion_lock; struct solo_dev* solo_dev; } ;
struct solo_dev {int motion_mask; } ;

/* Variables and functions */
 int SOLO_MOTION_EXT_ADDR (struct solo_dev*) ; 
 int SOLO_VI_MOTION_EN (int) ; 
 int /*<<< orphan*/  SOLO_VI_MOT_ADR ; 
 int /*<<< orphan*/  SOLO_VI_MOT_CLEAR ; 
 int /*<<< orphan*/  solo_reg_write (struct solo_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void solo_motion_toggle(struct solo_enc_dev *solo_enc, int on)
{
	struct solo_dev *solo_dev = solo_enc->solo_dev;
	u32 mask = 1 << solo_enc->ch;
	unsigned long flags;

	spin_lock_irqsave(&solo_enc->motion_lock, flags);

	if (on)
		solo_dev->motion_mask |= mask;
	else
		solo_dev->motion_mask &= ~mask;

	solo_reg_write(solo_dev, SOLO_VI_MOT_CLEAR, mask);

	solo_reg_write(solo_dev, SOLO_VI_MOT_ADR,
		       SOLO_VI_MOTION_EN(solo_dev->motion_mask) |
		       (SOLO_MOTION_EXT_ADDR(solo_dev) >> 16));

	spin_unlock_irqrestore(&solo_enc->motion_lock, flags);
}