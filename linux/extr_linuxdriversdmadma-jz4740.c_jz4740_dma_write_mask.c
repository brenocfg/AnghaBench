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
typedef  int /*<<< orphan*/  uint32_t ;
struct jz4740_dma_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  jz4740_dma_read (struct jz4740_dma_dev*,unsigned int) ; 
 int /*<<< orphan*/  jz4740_dma_write (struct jz4740_dma_dev*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void jz4740_dma_write_mask(struct jz4740_dma_dev *dmadev,
	unsigned int reg, uint32_t val, uint32_t mask)
{
	uint32_t tmp;

	tmp = jz4740_dma_read(dmadev, reg);
	tmp &= ~mask;
	tmp |= val;
	jz4740_dma_write(dmadev, reg, tmp);
}