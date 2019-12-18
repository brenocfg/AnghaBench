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
typedef  int u16 ;
struct dib8000_state {int dummy; } ;

/* Variables and functions */
 int* adc_target_16dB ; 
 int /*<<< orphan*/  dib8000_write_word (struct dib8000_state*,int,int) ; 

__attribute__((used)) static void dib8000_update_ana_gain(struct dib8000_state *state, u16 ana_gain)
{
	u16 i;

	dib8000_write_word(state, 116, ana_gain);

	/* update ADC target depending on ana_gain */
	if (ana_gain) { /* set -16dB ADC target for ana_gain=-1 */
		for (i = 0; i < 10; i++)
			dib8000_write_word(state, 80 + i, adc_target_16dB[i]);
	} else { /* set -22dB ADC target for ana_gain=0 */
		for (i = 0; i < 10; i++)
			dib8000_write_word(state, 80 + i, adc_target_16dB[i] - 355);
	}
}