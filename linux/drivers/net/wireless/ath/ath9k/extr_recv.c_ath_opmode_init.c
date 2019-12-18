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
typedef  int /*<<< orphan*/  u32 ;
struct ath_softc {struct ath_hw* sc_ah; } ;
struct ath_hw {int dummy; } ;
struct ath_common {int dummy; } ;

/* Variables and functions */
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_setmcastfilter (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_hw_setopmode (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_setrxfilter (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_calcrxfilter (struct ath_softc*) ; 
 int /*<<< orphan*/  ath_hw_setbssidmask (struct ath_common*) ; 

__attribute__((used)) static void ath_opmode_init(struct ath_softc *sc)
{
	struct ath_hw *ah = sc->sc_ah;
	struct ath_common *common = ath9k_hw_common(ah);

	u32 rfilt, mfilt[2];

	/* configure rx filter */
	rfilt = ath_calcrxfilter(sc);
	ath9k_hw_setrxfilter(ah, rfilt);

	/* configure bssid mask */
	ath_hw_setbssidmask(common);

	/* configure operational mode */
	ath9k_hw_setopmode(ah);

	/* calculate and install multicast filter */
	mfilt[0] = mfilt[1] = ~0;
	ath9k_hw_setmcastfilter(ah, mfilt[0], mfilt[1]);
}