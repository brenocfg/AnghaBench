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
struct ene_device {int /*<<< orphan*/  rdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENE_FW1 ; 
 int ENE_FW1_ENABLE ; 
 int ENE_FW1_IRQ ; 
 int /*<<< orphan*/  ene_clear_reg_mask (struct ene_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ene_rx_enable_cir_engine (struct ene_device*,int) ; 
 int /*<<< orphan*/  ene_rx_enable_fan_input (struct ene_device*,int) ; 
 int /*<<< orphan*/  ir_raw_event_set_idle (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ene_rx_disable_hw(struct ene_device *dev)
{
	/* disable inputs */
	ene_rx_enable_cir_engine(dev, false);
	ene_rx_enable_fan_input(dev, false);

	/* disable hardware IRQ and firmware flag */
	ene_clear_reg_mask(dev, ENE_FW1, ENE_FW1_ENABLE | ENE_FW1_IRQ);
	ir_raw_event_set_idle(dev->rdev, true);
}