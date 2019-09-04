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
typedef  int u16 ;
struct sky2_port {unsigned int port; struct sky2_hw* hw; } ;
struct sky2_hw {int dummy; } ;

/* Variables and functions */
 int GM_GPCR_RX_ENA ; 
 int GM_GPCR_TX_ENA ; 
 int /*<<< orphan*/  GM_GP_CTRL ; 
 int gma_read16 (struct sky2_hw*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gma_write16 (struct sky2_hw*,unsigned int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sky2_enable_rx_tx(struct sky2_port *sky2)
{
	struct sky2_hw *hw = sky2->hw;
	unsigned port = sky2->port;
	u16 reg;

	reg = gma_read16(hw, port, GM_GP_CTRL);
	reg |= GM_GPCR_RX_ENA | GM_GPCR_TX_ENA;
	gma_write16(hw, port, GM_GP_CTRL, reg);
}