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
struct at91_adc_state {int current_sample_rate; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned at91_adc_get_sample_freq(struct at91_adc_state *st)
{
	return st->current_sample_rate;
}