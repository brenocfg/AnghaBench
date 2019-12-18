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
struct ath_hw {int dummy; } ;
struct ath9k_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_PHY_GC_DYN2040_PRI_CH ; 
 int /*<<< orphan*/  AR_PHY_GEN_CTRL ; 
 scalar_t__ IS_CHAN_HT40 (struct ath9k_channel*) ; 
 int REG_READ_FIELD (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar9003_hw_spur_ofdm (struct ath_hw*,int,int,int,int,int,int) ; 

__attribute__((used)) static void ar9003_hw_spur_ofdm_work(struct ath_hw *ah,
				     struct ath9k_channel *chan,
				     int freq_offset,
				     int range,
				     int synth_freq)
{
	int spur_freq_sd = 0;
	int spur_subchannel_sd = 0;
	int spur_delta_phase = 0;

	if (IS_CHAN_HT40(chan)) {
		if (freq_offset < 0) {
			if (REG_READ_FIELD(ah, AR_PHY_GEN_CTRL,
					   AR_PHY_GC_DYN2040_PRI_CH) == 0x0)
				spur_subchannel_sd = 1;
			else
				spur_subchannel_sd = 0;

			spur_freq_sd = ((freq_offset + 10) << 9) / 11;

		} else {
			if (REG_READ_FIELD(ah, AR_PHY_GEN_CTRL,
			    AR_PHY_GC_DYN2040_PRI_CH) == 0x0)
				spur_subchannel_sd = 0;
			else
				spur_subchannel_sd = 1;

			spur_freq_sd = ((freq_offset - 10) << 9) / 11;

		}

		spur_delta_phase = (freq_offset << 17) / 5;

	} else {
		spur_subchannel_sd = 0;
		spur_freq_sd = (freq_offset << 9) /11;
		spur_delta_phase = (freq_offset << 18) / 5;
	}

	spur_freq_sd = spur_freq_sd & 0x3ff;
	spur_delta_phase = spur_delta_phase & 0xfffff;

	ar9003_hw_spur_ofdm(ah,
			    freq_offset,
			    spur_freq_sd,
			    spur_delta_phase,
			    spur_subchannel_sd,
			    range, synth_freq);
}