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
struct sudmac_regs {int /*<<< orphan*/  base_byte_count; int /*<<< orphan*/  base_addr; } ;
struct sudmac_chan {scalar_t__ offset; int /*<<< orphan*/  cfg; } ;
struct shdma_desc {int dummy; } ;

/* Variables and functions */
 scalar_t__ SUDMAC_CH0BA ; 
 scalar_t__ SUDMAC_CH0BBC ; 
 scalar_t__ SUDMAC_CH0CFG ; 
 int /*<<< orphan*/  sudmac_writel (struct sudmac_chan*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void sudmac_set_reg(struct sudmac_chan *sc, struct sudmac_regs *hw,
			   struct shdma_desc *sdesc)
{
	sudmac_writel(sc, sc->cfg, SUDMAC_CH0CFG + sc->offset);
	sudmac_writel(sc, hw->base_addr, SUDMAC_CH0BA + sc->offset);
	sudmac_writel(sc, hw->base_byte_count, SUDMAC_CH0BBC + sc->offset);
}