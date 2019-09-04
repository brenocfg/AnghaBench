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
typedef  int u8 ;
struct ene_device {scalar_t__ hw_revision; int irq; int /*<<< orphan*/  rdev; int /*<<< orphan*/  rx_fan_input_inuse; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENEB_IRQ ; 
 int /*<<< orphan*/  ENEB_IRQ_UNK1 ; 
 int /*<<< orphan*/  ENE_FW1 ; 
 int ENE_FW1_ENABLE ; 
 int ENE_FW1_IRQ ; 
 scalar_t__ ENE_HW_C ; 
 int /*<<< orphan*/  ENE_IRQ ; 
 int ENE_IRQ_MASK ; 
 int ENE_IRQ_STATUS ; 
 int ENE_IRQ_UNK_EN ; 
 int /*<<< orphan*/  ene_irq_status (struct ene_device*) ; 
 int ene_read_reg (struct ene_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ene_rx_enable_cir_engine (struct ene_device*,int) ; 
 int /*<<< orphan*/  ene_rx_enable_fan_input (struct ene_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ene_set_reg_mask (struct ene_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ene_write_reg (struct ene_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ir_raw_event_set_idle (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ene_rx_enable_hw(struct ene_device *dev)
{
	u8 reg_value;

	/* Enable system interrupt */
	if (dev->hw_revision < ENE_HW_C) {
		ene_write_reg(dev, ENEB_IRQ, dev->irq << 1);
		ene_write_reg(dev, ENEB_IRQ_UNK1, 0x01);
	} else {
		reg_value = ene_read_reg(dev, ENE_IRQ) & 0xF0;
		reg_value |= ENE_IRQ_UNK_EN;
		reg_value &= ~ENE_IRQ_STATUS;
		reg_value |= (dev->irq & ENE_IRQ_MASK);
		ene_write_reg(dev, ENE_IRQ, reg_value);
	}

	/* Enable inputs */
	ene_rx_enable_fan_input(dev, dev->rx_fan_input_inuse);
	ene_rx_enable_cir_engine(dev, !dev->rx_fan_input_inuse);

	/* ack any pending irqs - just in case */
	ene_irq_status(dev);

	/* enable firmware bits */
	ene_set_reg_mask(dev, ENE_FW1, ENE_FW1_ENABLE | ENE_FW1_IRQ);

	/* enter idle mode */
	ir_raw_event_set_idle(dev->rdev, true);
}