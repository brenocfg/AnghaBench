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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct ath_common {int /*<<< orphan*/  macaddr; } ;
struct ath5k_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR5K_STA_ID0 ; 
 int /*<<< orphan*/  AR5K_STA_ID1 ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 struct ath_common* ath5k_hw_common (struct ath5k_hw*) ; 
 int ath5k_hw_reg_read (struct ath5k_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath5k_hw_reg_write (struct ath5k_hw*,int,int /*<<< orphan*/ ) ; 
 int get_unaligned_le16 (int /*<<< orphan*/  const*) ; 
 int get_unaligned_le32 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

int
ath5k_hw_set_lladdr(struct ath5k_hw *ah, const u8 *mac)
{
	struct ath_common *common = ath5k_hw_common(ah);
	u32 low_id, high_id;
	u32 pcu_reg;

	/* Set new station ID */
	memcpy(common->macaddr, mac, ETH_ALEN);

	pcu_reg = ath5k_hw_reg_read(ah, AR5K_STA_ID1) & 0xffff0000;

	low_id = get_unaligned_le32(mac);
	high_id = get_unaligned_le16(mac + 4);

	ath5k_hw_reg_write(ah, low_id, AR5K_STA_ID0);
	ath5k_hw_reg_write(ah, pcu_reg | high_id, AR5K_STA_ID1);

	return 0;
}