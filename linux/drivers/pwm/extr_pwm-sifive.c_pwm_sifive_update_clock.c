#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long long u64 ;
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct pwm_sifive_ddata {unsigned long long approx_period; void* real_period; TYPE_1__ chip; scalar_t__ regs; } ;

/* Variables and functions */
 int FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 unsigned long NSEC_PER_SEC ; 
 int PWM_SIFIVE_CMPWIDTH ; 
 scalar_t__ PWM_SIFIVE_PWMCFG ; 
 int PWM_SIFIVE_PWMCFG_EN_ALWAYS ; 
 int /*<<< orphan*/  PWM_SIFIVE_PWMCFG_SCALE ; 
 int clamp (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,void*) ; 
 void* div64_ul (unsigned long long,unsigned long) ; 
 scalar_t__ ilog2 (unsigned long) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void pwm_sifive_update_clock(struct pwm_sifive_ddata *ddata,
				    unsigned long rate)
{
	unsigned long long num;
	unsigned long scale_pow;
	int scale;
	u32 val;
	/*
	 * The PWM unit is used with pwmzerocmp=0, so the only way to modify the
	 * period length is using pwmscale which provides the number of bits the
	 * counter is shifted before being feed to the comparators. A period
	 * lasts (1 << (PWM_SIFIVE_CMPWIDTH + pwmscale)) clock ticks.
	 * (1 << (PWM_SIFIVE_CMPWIDTH + scale)) * 10^9/rate = period
	 */
	scale_pow = div64_ul(ddata->approx_period * (u64)rate, NSEC_PER_SEC);
	scale = clamp(ilog2(scale_pow) - PWM_SIFIVE_CMPWIDTH, 0, 0xf);

	val = PWM_SIFIVE_PWMCFG_EN_ALWAYS |
	      FIELD_PREP(PWM_SIFIVE_PWMCFG_SCALE, scale);
	writel(val, ddata->regs + PWM_SIFIVE_PWMCFG);

	/* As scale <= 15 the shift operation cannot overflow. */
	num = (unsigned long long)NSEC_PER_SEC << (PWM_SIFIVE_CMPWIDTH + scale);
	ddata->real_period = div64_ul(num, rate);
	dev_dbg(ddata->chip.dev,
		"New real_period = %u ns\n", ddata->real_period);
}