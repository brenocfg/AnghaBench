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
struct snd_tea575x {int freq; int band; int val; } ;

/* Variables and functions */
#define  BAND_AM 130 
#define  BAND_FM 129 
#define  BAND_FM_JAPAN 128 
 int TEA575X_AMIF ; 
 int TEA575X_BIT_BAND_FM ; 
 int TEA575X_BIT_BAND_MASK ; 
 int TEA575X_BIT_BAND_MW ; 
 int TEA575X_BIT_FREQ_MASK ; 
 int TEA575X_FMIF ; 
 int snd_tea575x_val_to_freq (struct snd_tea575x*,int) ; 
 int /*<<< orphan*/  snd_tea575x_write (struct snd_tea575x*,int) ; 

void snd_tea575x_set_freq(struct snd_tea575x *tea)
{
	u32 freq = tea->freq / 16;	/* to kHz */
	u32 band = 0;

	switch (tea->band) {
	case BAND_FM:
		band = TEA575X_BIT_BAND_FM;
		/* crystal fixup */
		freq += TEA575X_FMIF;
		/* freq /= 12.5 */
		freq *= 10;
		freq /= 125;
		break;
	case BAND_FM_JAPAN:
		band = TEA575X_BIT_BAND_FM;
		/* crystal fixup */
		freq -= TEA575X_FMIF;
		/* freq /= 12.5 */
		freq *= 10;
		freq /= 125;
		break;
	case BAND_AM:
		band = TEA575X_BIT_BAND_MW;
		/* crystal fixup */
		freq += TEA575X_AMIF;
		break;
	}

	tea->val &= ~(TEA575X_BIT_FREQ_MASK | TEA575X_BIT_BAND_MASK);
	tea->val |= band;
	tea->val |= freq & TEA575X_BIT_FREQ_MASK;
	snd_tea575x_write(tea, tea->val);
	tea->freq = snd_tea575x_val_to_freq(tea, tea->val);
}