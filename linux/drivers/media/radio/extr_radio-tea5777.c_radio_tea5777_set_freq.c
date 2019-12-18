#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct radio_tea5777 {size_t band; int write_reg; int needs_write; int read_reg; int /*<<< orphan*/  freq; TYPE_1__* ops; int /*<<< orphan*/  audmode; } ;
struct TYPE_4__ {int /*<<< orphan*/  rangehigh; int /*<<< orphan*/  rangelow; } ;
struct TYPE_3__ {int (* write_reg ) (struct radio_tea5777*,long long) ;} ;

/* Variables and functions */
#define  BAND_AM 129 
#define  BAND_FM 128 
 int TEA5777_AM_FREQ_STEP ; 
 int /*<<< orphan*/  TEA5777_AM_IF ; 
 int TEA5777_FM_FREQ_STEP ; 
 int /*<<< orphan*/  TEA5777_FM_IF ; 
 int TEA5777_W_AM_AGCRF_MASK ; 
 long long TEA5777_W_AM_CALLIGN_MASK ; 
 int TEA5777_W_AM_FM_MASK ; 
 long long TEA5777_W_AM_FM_SHIFT ; 
 int TEA5777_W_AM_LNA_MASK ; 
 long long TEA5777_W_AM_LNA_SHIFT ; 
 int TEA5777_W_AM_MW ; 
 int TEA5777_W_AM_MWLW_MASK ; 
 int TEA5777_W_AM_MWLW_SHIFT ; 
 long long TEA5777_W_AM_PEAK_MASK ; 
 long long TEA5777_W_AM_PEAK_SHIFT ; 
 long long TEA5777_W_AM_PLL_MASK ; 
 int TEA5777_W_AM_PLL_SHIFT ; 
 int TEA5777_W_FM_FORCEMONO_MASK ; 
 long long TEA5777_W_FM_FORCEMONO_SHIFT ; 
 int TEA5777_W_FM_FREF_MASK ; 
 int TEA5777_W_FM_FREF_SHIFT ; 
 int TEA5777_W_FM_FREF_VALUE ; 
 int TEA5777_W_FM_PLL_MASK ; 
 int TEA5777_W_FM_PLL_SHIFT ; 
 int /*<<< orphan*/  V4L2_TUNER_MODE_MONO ; 
 TYPE_2__* bands ; 
 int clamp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct radio_tea5777*,long long) ; 
 int /*<<< orphan*/  tea5777_freq_to_v4l2_freq (struct radio_tea5777*,int) ; 

int radio_tea5777_set_freq(struct radio_tea5777 *tea)
{
	u32 freq;
	int res;

	freq = clamp(tea->freq, bands[tea->band].rangelow,
				bands[tea->band].rangehigh);
	freq = (freq + 8) / 16; /* to kHz */

	switch (tea->band) {
	case BAND_FM:
		tea->write_reg &= ~TEA5777_W_AM_FM_MASK;
		freq = (freq - TEA5777_FM_IF) / TEA5777_FM_FREQ_STEP;
		tea->write_reg &= ~TEA5777_W_FM_PLL_MASK;
		tea->write_reg |= (u64)freq << TEA5777_W_FM_PLL_SHIFT;
		tea->write_reg &= ~TEA5777_W_FM_FREF_MASK;
		tea->write_reg |= TEA5777_W_FM_FREF_VALUE <<
				  TEA5777_W_FM_FREF_SHIFT;
		tea->write_reg &= ~TEA5777_W_FM_FORCEMONO_MASK;
		if (tea->audmode == V4L2_TUNER_MODE_MONO)
			tea->write_reg |= 1LL << TEA5777_W_FM_FORCEMONO_SHIFT;
		break;
	case BAND_AM:
		tea->write_reg &= ~TEA5777_W_AM_FM_MASK;
		tea->write_reg |= (1LL << TEA5777_W_AM_FM_SHIFT);
		freq = (freq - TEA5777_AM_IF) / TEA5777_AM_FREQ_STEP;
		tea->write_reg &= ~TEA5777_W_AM_PLL_MASK;
		tea->write_reg |= (u64)freq << TEA5777_W_AM_PLL_SHIFT;
		tea->write_reg &= ~TEA5777_W_AM_AGCRF_MASK;
		tea->write_reg &= ~TEA5777_W_AM_AGCRF_MASK;
		tea->write_reg &= ~TEA5777_W_AM_MWLW_MASK;
		tea->write_reg |= TEA5777_W_AM_MW << TEA5777_W_AM_MWLW_SHIFT;
		tea->write_reg &= ~TEA5777_W_AM_LNA_MASK;
		tea->write_reg |= 1LL << TEA5777_W_AM_LNA_SHIFT;
		tea->write_reg &= ~TEA5777_W_AM_PEAK_MASK;
		tea->write_reg |= 1LL << TEA5777_W_AM_PEAK_SHIFT;
		tea->write_reg &= ~TEA5777_W_AM_CALLIGN_MASK;
		break;
	}

	res = tea->ops->write_reg(tea, tea->write_reg);
	if (res)
		return res;

	tea->needs_write = false;
	tea->read_reg = -1;
	tea->freq = tea5777_freq_to_v4l2_freq(tea, freq);

	return 0;
}