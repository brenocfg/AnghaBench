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
typedef  int uint8_t ;
struct r852_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  R852_CARD_IRQ_ENABLE ; 
 int R852_CARD_IRQ_MASK ; 
 int /*<<< orphan*/  R852_CARD_IRQ_STA ; 
 int /*<<< orphan*/  R852_DMA_IRQ_ENABLE ; 
 int R852_DMA_IRQ_MASK ; 
 int /*<<< orphan*/  R852_DMA_IRQ_STA ; 
 int r852_read_reg (struct r852_device*,int /*<<< orphan*/ ) ; 
 int r852_read_reg_dword (struct r852_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r852_write_reg (struct r852_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r852_write_reg_dword (struct r852_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void r852_disable_irqs(struct r852_device *dev)
{
	uint8_t reg;
	reg = r852_read_reg(dev, R852_CARD_IRQ_ENABLE);
	r852_write_reg(dev, R852_CARD_IRQ_ENABLE, reg & ~R852_CARD_IRQ_MASK);

	reg = r852_read_reg_dword(dev, R852_DMA_IRQ_ENABLE);
	r852_write_reg_dword(dev, R852_DMA_IRQ_ENABLE,
					reg & ~R852_DMA_IRQ_MASK);

	r852_write_reg(dev, R852_CARD_IRQ_STA, R852_CARD_IRQ_MASK);
	r852_write_reg_dword(dev, R852_DMA_IRQ_STA, R852_DMA_IRQ_MASK);
}