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
typedef  int u64 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct skge_port {int dma; int mem; struct skge_hw* hw; } ;
struct skge_hw {int dummy; } ;
struct skge_element {int desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  B0_CTST ; 
 int CSR_CLR_RESET ; 
 int CS_BUS_CLOCK ; 
 int CS_BUS_SLOT_SZ ; 
 int /*<<< orphan*/  Q_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Q_CSR ; 
 int /*<<< orphan*/  Q_DA_H ; 
 int /*<<< orphan*/  Q_DA_L ; 
 int /*<<< orphan*/  Q_F ; 
 int skge_read16 (struct skge_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skge_write32 (struct skge_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void skge_qset(struct skge_port *skge, u16 q,
		      const struct skge_element *e)
{
	struct skge_hw *hw = skge->hw;
	u32 watermark = 0x600;
	u64 base = skge->dma + (e->desc - skge->mem);

	/* optimization to reduce window on 32bit/33mhz */
	if ((skge_read16(hw, B0_CTST) & (CS_BUS_CLOCK | CS_BUS_SLOT_SZ)) == 0)
		watermark /= 2;

	skge_write32(hw, Q_ADDR(q, Q_CSR), CSR_CLR_RESET);
	skge_write32(hw, Q_ADDR(q, Q_F), watermark);
	skge_write32(hw, Q_ADDR(q, Q_DA_H), (u32)(base >> 32));
	skge_write32(hw, Q_ADDR(q, Q_DA_L), (u32)base);
}