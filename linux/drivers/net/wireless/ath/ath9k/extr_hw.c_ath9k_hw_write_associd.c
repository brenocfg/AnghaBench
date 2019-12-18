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
struct ath_common {int curaid; scalar_t__ curbssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_BSS_ID0 ; 
 int /*<<< orphan*/  AR_BSS_ID1 ; 
 int AR_BSS_ID1_AID_S ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int get_unaligned_le16 (scalar_t__) ; 
 int get_unaligned_le32 (scalar_t__) ; 

void ath9k_hw_write_associd(struct ath_hw *ah)
{
	struct ath_common *common = ath9k_hw_common(ah);

	REG_WRITE(ah, AR_BSS_ID0, get_unaligned_le32(common->curbssid));
	REG_WRITE(ah, AR_BSS_ID1, get_unaligned_le16(common->curbssid + 4) |
		  ((common->curaid & 0x3fff) << AR_BSS_ID1_AID_S));
}