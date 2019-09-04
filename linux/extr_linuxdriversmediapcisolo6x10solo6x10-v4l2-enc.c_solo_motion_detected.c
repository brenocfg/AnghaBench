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
struct solo_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOLO_VI_MOT_CLEAR ; 
 int /*<<< orphan*/  SOLO_VI_MOT_STATUS ; 
 int solo_reg_read (struct solo_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  solo_reg_write (struct solo_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int solo_motion_detected(struct solo_enc_dev *solo_enc)
{
	struct solo_dev *solo_dev = solo_enc->solo_dev;
	unsigned long flags;
	u32 ch_mask = 1 << solo_enc->ch;
	int ret = 0;

	spin_lock_irqsave(&solo_enc->motion_lock, flags);
	if (solo_reg_read(solo_dev, SOLO_VI_MOT_STATUS) & ch_mask) {
		solo_reg_write(solo_dev, SOLO_VI_MOT_CLEAR, ch_mask);
		ret = 1;
	}
	spin_unlock_irqrestore(&solo_enc->motion_lock, flags);

	return ret;
}