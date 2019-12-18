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
struct stk1160 {int dummy; } ;

/* Variables and functions */
 scalar_t__ STK1160_AC97CTL_0 ; 
 scalar_t__ STK1160_AC97CTL_1 ; 
 int /*<<< orphan*/  stk1160_ac97_dump_regs (struct stk1160*) ; 
 int /*<<< orphan*/  stk1160_has_ac97 (struct stk1160*) ; 
 int /*<<< orphan*/  stk1160_has_audio (struct stk1160*) ; 
 int /*<<< orphan*/  stk1160_info (char*) ; 
 int /*<<< orphan*/  stk1160_write_ac97 (struct stk1160*,int,int) ; 
 int /*<<< orphan*/  stk1160_write_reg (struct stk1160*,scalar_t__,int) ; 

void stk1160_ac97_setup(struct stk1160 *dev)
{
	if (!stk1160_has_audio(dev)) {
		stk1160_info("Device doesn't support audio, skipping AC97 setup.");
		return;
	}

	if (!stk1160_has_ac97(dev)) {
		stk1160_info("Device uses internal 8-bit ADC, skipping AC97 setup.");
		return;
	}

	/* Two-step reset AC97 interface and hardware codec */
	stk1160_write_reg(dev, STK1160_AC97CTL_0, 0x94);
	stk1160_write_reg(dev, STK1160_AC97CTL_0, 0x8c);

	/* Set 16-bit audio data and choose L&R channel*/
	stk1160_write_reg(dev, STK1160_AC97CTL_1 + 2, 0x01);
	stk1160_write_reg(dev, STK1160_AC97CTL_1 + 3, 0x00);

	/* Setup channels */
	stk1160_write_ac97(dev, 0x12, 0x8808); /* CD volume */
	stk1160_write_ac97(dev, 0x10, 0x0808); /* Line-in volume */
	stk1160_write_ac97(dev, 0x0e, 0x0008); /* MIC volume (mono) */
	stk1160_write_ac97(dev, 0x16, 0x0808); /* Aux volume */
	stk1160_write_ac97(dev, 0x1a, 0x0404); /* Record select */
	stk1160_write_ac97(dev, 0x02, 0x0000); /* Master volume */
	stk1160_write_ac97(dev, 0x1c, 0x0808); /* Record gain */

#ifdef DEBUG
	stk1160_ac97_dump_regs(dev);
#endif
}