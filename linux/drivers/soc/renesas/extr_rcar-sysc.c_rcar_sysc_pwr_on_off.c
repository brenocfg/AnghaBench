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
struct rcar_sysc_ch {unsigned int chan_bit; scalar_t__ chan_offs; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 int EAGAIN ; 
 unsigned int PWROFFCR_OFFS ; 
 unsigned int PWRONCR_OFFS ; 
 scalar_t__ SYSCSR ; 
 int /*<<< orphan*/  SYSCSR_DELAY_US ; 
 unsigned int SYSCSR_POFFENB ; 
 unsigned int SYSCSR_PONENB ; 
 int SYSCSR_RETRIES ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 scalar_t__ rcar_sysc_base ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rcar_sysc_pwr_on_off(const struct rcar_sysc_ch *sysc_ch, bool on)
{
	unsigned int sr_bit, reg_offs;
	int k;

	if (on) {
		sr_bit = SYSCSR_PONENB;
		reg_offs = PWRONCR_OFFS;
	} else {
		sr_bit = SYSCSR_POFFENB;
		reg_offs = PWROFFCR_OFFS;
	}

	/* Wait until SYSC is ready to accept a power request */
	for (k = 0; k < SYSCSR_RETRIES; k++) {
		if (ioread32(rcar_sysc_base + SYSCSR) & BIT(sr_bit))
			break;
		udelay(SYSCSR_DELAY_US);
	}

	if (k == SYSCSR_RETRIES)
		return -EAGAIN;

	/* Submit power shutoff or power resume request */
	iowrite32(BIT(sysc_ch->chan_bit),
		  rcar_sysc_base + sysc_ch->chan_offs + reg_offs);

	return 0;
}