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
struct alx_hw {int /*<<< orphan*/  rx_ctrl; } ;
struct alx_priv {int /*<<< orphan*/  dev; struct alx_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALX_MAC_CTRL ; 
 int /*<<< orphan*/  __alx_set_rx_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alx_configure_basic (struct alx_hw*) ; 
 int /*<<< orphan*/  alx_disable_rss (struct alx_hw*) ; 
 int /*<<< orphan*/  alx_write_mem32 (struct alx_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void alx_configure(struct alx_priv *alx)
{
	struct alx_hw *hw = &alx->hw;

	alx_configure_basic(hw);
	alx_disable_rss(hw);
	__alx_set_rx_mode(alx->dev);

	alx_write_mem32(hw, ALX_MAC_CTRL, hw->rx_ctrl);
}