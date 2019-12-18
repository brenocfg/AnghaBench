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
struct ath_hw {int /*<<< orphan*/  ah_mibStats; } ;
struct ath_common {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANI ; 
 int /*<<< orphan*/  AR_FILT_CCK ; 
 int /*<<< orphan*/  AR_FILT_OFDM ; 
 int /*<<< orphan*/  AR_MIBC ; 
 int AR_MIBC_CMC ; 
 int AR_MIBC_COW ; 
 int AR_MIBC_FMC ; 
 int AR_MIBC_MCS ; 
 int AR_PHY_ERR_CCK_TIMING ; 
 int /*<<< orphan*/  AR_PHY_ERR_MASK_1 ; 
 int /*<<< orphan*/  AR_PHY_ERR_MASK_2 ; 
 int AR_PHY_ERR_OFDM_TIMING ; 
 int /*<<< orphan*/  ENABLE_REGWRITE_BUFFER (struct ath_hw*) ; 
 int /*<<< orphan*/  REGWRITE_BUFFER_FLUSH (struct ath_hw*) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_update_mibstats (struct ath_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*) ; 

void ath9k_enable_mib_counters(struct ath_hw *ah)
{
	struct ath_common *common = ath9k_hw_common(ah);

	ath_dbg(common, ANI, "Enable MIB counters\n");

	ath9k_hw_update_mibstats(ah, &ah->ah_mibStats);

	ENABLE_REGWRITE_BUFFER(ah);

	REG_WRITE(ah, AR_FILT_OFDM, 0);
	REG_WRITE(ah, AR_FILT_CCK, 0);
	REG_WRITE(ah, AR_MIBC,
		  ~(AR_MIBC_COW | AR_MIBC_FMC | AR_MIBC_CMC | AR_MIBC_MCS)
		  & 0x0f);
	REG_WRITE(ah, AR_PHY_ERR_MASK_1, AR_PHY_ERR_OFDM_TIMING);
	REG_WRITE(ah, AR_PHY_ERR_MASK_2, AR_PHY_ERR_CCK_TIMING);

	REGWRITE_BUFFER_FLUSH(ah);
}