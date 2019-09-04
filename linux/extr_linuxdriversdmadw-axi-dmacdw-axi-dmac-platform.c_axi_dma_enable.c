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
typedef  int /*<<< orphan*/  u32 ;
struct axi_dma_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMAC_CFG ; 
 int /*<<< orphan*/  DMAC_EN_MASK ; 
 int /*<<< orphan*/  axi_dma_ioread32 (struct axi_dma_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  axi_dma_iowrite32 (struct axi_dma_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void axi_dma_enable(struct axi_dma_chip *chip)
{
	u32 val;

	val = axi_dma_ioread32(chip, DMAC_CFG);
	val |= DMAC_EN_MASK;
	axi_dma_iowrite32(chip, DMAC_CFG, val);
}