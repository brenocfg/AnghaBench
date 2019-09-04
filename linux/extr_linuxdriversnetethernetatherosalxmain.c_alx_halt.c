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
struct alx_hw {int /*<<< orphan*/  duplex; int /*<<< orphan*/  link_speed; } ;
struct alx_priv {struct alx_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUPLEX_UNKNOWN ; 
 int /*<<< orphan*/  SPEED_UNKNOWN ; 
 int /*<<< orphan*/  alx_enable_aspm (struct alx_hw*,int,int) ; 
 int /*<<< orphan*/  alx_free_buffers (struct alx_priv*) ; 
 int /*<<< orphan*/  alx_irq_disable (struct alx_priv*) ; 
 int /*<<< orphan*/  alx_netif_stop (struct alx_priv*) ; 
 int /*<<< orphan*/  alx_reset_mac (struct alx_hw*) ; 

__attribute__((used)) static void alx_halt(struct alx_priv *alx)
{
	struct alx_hw *hw = &alx->hw;

	alx_netif_stop(alx);
	hw->link_speed = SPEED_UNKNOWN;
	hw->duplex = DUPLEX_UNKNOWN;

	alx_reset_mac(hw);

	/* disable l0s/l1 */
	alx_enable_aspm(hw, false, false);
	alx_irq_disable(alx);
	alx_free_buffers(alx);
}