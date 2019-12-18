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
typedef  int /*<<< orphan*/  u32 ;
struct ath_hw {int dummy; } ;
struct ath_common {scalar_t__ priv; } ;
struct ath9k_htc_priv {TYPE_1__* wmi; int /*<<< orphan*/  fw_flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  m_rmw_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  HTC_FWFLAG_NO_RMW ; 
 int /*<<< orphan*/  REG_READ (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_reg_rmw_buffer (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_reg_rmw_single (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 ath9k_reg_rmw(void *hw_priv, u32 reg_offset, u32 set, u32 clr)
{
	struct ath_hw *ah = hw_priv;
	struct ath_common *common = ath9k_hw_common(ah);
	struct ath9k_htc_priv *priv = (struct ath9k_htc_priv *) common->priv;

	if (test_bit(HTC_FWFLAG_NO_RMW, &priv->fw_flags)) {
		u32 val;

		val = REG_READ(ah, reg_offset);
		val &= ~clr;
		val |= set;
		REG_WRITE(ah, reg_offset, val);

		return 0;
	}

	if (atomic_read(&priv->wmi->m_rmw_cnt))
		ath9k_reg_rmw_buffer(hw_priv, reg_offset, set, clr);
	else
		ath9k_reg_rmw_single(hw_priv, reg_offset, set, clr);

	return 0;
}