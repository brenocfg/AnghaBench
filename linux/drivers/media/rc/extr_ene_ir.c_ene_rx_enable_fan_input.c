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
struct ene_device {int /*<<< orphan*/  hw_fan_input; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENE_FAN_AS_IN1 ; 
 int /*<<< orphan*/  ENE_FAN_AS_IN1_EN ; 
 int /*<<< orphan*/  ENE_FAN_AS_IN2 ; 
 int /*<<< orphan*/  ENE_FAN_AS_IN2_EN ; 
 int /*<<< orphan*/  ene_write_reg (struct ene_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ene_rx_enable_fan_input(struct ene_device *dev, bool enable)
{
	if (!dev->hw_fan_input)
		return;

	if (!enable)
		ene_write_reg(dev, ENE_FAN_AS_IN1, 0);
	else {
		ene_write_reg(dev, ENE_FAN_AS_IN1, ENE_FAN_AS_IN1_EN);
		ene_write_reg(dev, ENE_FAN_AS_IN2, ENE_FAN_AS_IN2_EN);
	}
}