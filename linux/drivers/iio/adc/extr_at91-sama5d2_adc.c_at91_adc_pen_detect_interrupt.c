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
struct TYPE_2__ {int touching; int /*<<< orphan*/  sample_period_val; } ;
struct at91_adc_state {TYPE_1__ touch_st; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_SAMA5D2_IDR ; 
 int /*<<< orphan*/  AT91_SAMA5D2_IER ; 
 int AT91_SAMA5D2_IER_NOPEN ; 
 int AT91_SAMA5D2_IER_PEN ; 
 int AT91_SAMA5D2_IER_PRDY ; 
 int AT91_SAMA5D2_IER_XRDY ; 
 int AT91_SAMA5D2_IER_YRDY ; 
 int /*<<< orphan*/  AT91_SAMA5D2_TRGR ; 
 int AT91_SAMA5D2_TRGR_TRGMOD_PERIODIC ; 
 int AT91_SAMA5D2_TRGR_TRGPER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  at91_adc_writel (struct at91_adc_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void at91_adc_pen_detect_interrupt(struct at91_adc_state *st)
{
	at91_adc_writel(st, AT91_SAMA5D2_IDR, AT91_SAMA5D2_IER_PEN);
	at91_adc_writel(st, AT91_SAMA5D2_IER, AT91_SAMA5D2_IER_NOPEN |
			AT91_SAMA5D2_IER_XRDY | AT91_SAMA5D2_IER_YRDY |
			AT91_SAMA5D2_IER_PRDY);
	at91_adc_writel(st, AT91_SAMA5D2_TRGR,
			AT91_SAMA5D2_TRGR_TRGMOD_PERIODIC |
			AT91_SAMA5D2_TRGR_TRGPER(st->touch_st.sample_period_val));
	st->touch_st.touching = true;
}