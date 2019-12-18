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
typedef  unsigned int u32 ;
struct brcmstb_pwm {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 unsigned int CTRL_CHAN_OFFS ; 
 unsigned int CTRL_OEB ; 
 unsigned int CTRL_OPENDRAIN ; 
 unsigned int CTRL_START ; 
 int /*<<< orphan*/  PWM_CTRL ; 
 unsigned int brcmstb_pwm_readl (struct brcmstb_pwm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmstb_pwm_writel (struct brcmstb_pwm*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void brcmstb_pwm_enable_set(struct brcmstb_pwm *p,
					  unsigned int channel, bool enable)
{
	unsigned int shift = channel * CTRL_CHAN_OFFS;
	u32 value;

	spin_lock(&p->lock);
	value = brcmstb_pwm_readl(p, PWM_CTRL);

	if (enable) {
		value &= ~(CTRL_OEB << shift);
		value |= (CTRL_START | CTRL_OPENDRAIN) << shift;
	} else {
		value &= ~((CTRL_START | CTRL_OPENDRAIN) << shift);
		value |= CTRL_OEB << shift;
	}

	brcmstb_pwm_writel(p, value, PWM_CTRL);
	spin_unlock(&p->lock);
}