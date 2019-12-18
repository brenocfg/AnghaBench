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
typedef  int u32 ;
struct snd_tea575x {int band; } ;
struct TYPE_2__ {int /*<<< orphan*/  rangehigh; int /*<<< orphan*/  rangelow; } ;

/* Variables and functions */
#define  BAND_AM 130 
#define  BAND_FM 129 
#define  BAND_FM_JAPAN 128 
 int TEA575X_AMIF ; 
 int TEA575X_BIT_FREQ_MASK ; 
 int TEA575X_FMIF ; 
 TYPE_1__* bands ; 
 int clamp (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 snd_tea575x_val_to_freq(struct snd_tea575x *tea, u32 val)
{
	u32 freq = val & TEA575X_BIT_FREQ_MASK;

	if (freq == 0)
		return freq;

	switch (tea->band) {
	case BAND_FM:
		/* freq *= 12.5 */
		freq *= 125;
		freq /= 10;
		/* crystal fixup */
		freq -= TEA575X_FMIF;
		break;
	case BAND_FM_JAPAN:
		/* freq *= 12.5 */
		freq *= 125;
		freq /= 10;
		/* crystal fixup */
		freq += TEA575X_FMIF;
		break;
	case BAND_AM:
		/* crystal fixup */
		freq -= TEA575X_AMIF;
		break;
	}

	return clamp(freq * 16, bands[tea->band].rangelow,
				bands[tea->band].rangehigh); /* from kHz */
}