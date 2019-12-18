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
struct survey_info {int /*<<< orphan*/  noise; int /*<<< orphan*/  filled; } ;
struct ath_softc {struct survey_info* survey; struct ath_hw* sc_ah; } ;
struct ath_hw {struct ath9k_channel* channels; } ;
struct ath9k_channel {scalar_t__ noisefloor; } ;

/* Variables and functions */
 int /*<<< orphan*/  SURVEY_INFO_NOISE_DBM ; 
 int /*<<< orphan*/  ath9k_hw_getchan_noise (struct ath_hw*,struct ath9k_channel*,scalar_t__) ; 

void ath_update_survey_nf(struct ath_softc *sc, int channel)
{
	struct ath_hw *ah = sc->sc_ah;
	struct ath9k_channel *chan = &ah->channels[channel];
	struct survey_info *survey = &sc->survey[channel];

	if (chan->noisefloor) {
		survey->filled |= SURVEY_INFO_NOISE_DBM;
		survey->noise = ath9k_hw_getchan_noise(ah, chan,
						       chan->noisefloor);
	}
}