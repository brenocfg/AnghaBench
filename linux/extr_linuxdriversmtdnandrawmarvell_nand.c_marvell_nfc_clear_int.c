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
typedef  int u32 ;
struct marvell_nfc {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ NDSR ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static u32 marvell_nfc_clear_int(struct marvell_nfc *nfc, u32 int_mask)
{
	u32 reg;

	reg = readl_relaxed(nfc->regs + NDSR);
	writel_relaxed(int_mask, nfc->regs + NDSR);

	return reg & int_mask;
}