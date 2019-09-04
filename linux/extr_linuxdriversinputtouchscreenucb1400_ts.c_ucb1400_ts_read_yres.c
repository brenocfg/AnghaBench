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
struct ucb1400_ts {int /*<<< orphan*/  ac97; } ;

/* Variables and functions */
 int /*<<< orphan*/  UCB_TS_CR ; 
 int UCB_TS_CR_BIAS_ENA ; 
 int UCB_TS_CR_MODE_PRES ; 
 int UCB_TS_CR_TSMY_GND ; 
 int UCB_TS_CR_TSPY_POW ; 
 int /*<<< orphan*/  adcsync ; 
 unsigned int ucb1400_adc_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucb1400_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static unsigned int ucb1400_ts_read_yres(struct ucb1400_ts *ucb)
{
	ucb1400_reg_write(ucb->ac97, UCB_TS_CR,
			UCB_TS_CR_TSMY_GND | UCB_TS_CR_TSPY_POW |
			UCB_TS_CR_MODE_PRES | UCB_TS_CR_BIAS_ENA);
	return ucb1400_adc_read(ucb->ac97, 0, adcsync);
}