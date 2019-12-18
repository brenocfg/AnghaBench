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
struct rc_dev {struct ene_device* priv; } ;
struct ene_device {int /*<<< orphan*/  tx_duty_cycle; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ene_tx_set_carrier (struct ene_device*) ; 

__attribute__((used)) static int ene_set_tx_duty_cycle(struct rc_dev *rdev, u32 duty_cycle)
{
	struct ene_device *dev = rdev->priv;
	dbg("TX: setting duty cycle to %d%%", duty_cycle);
	dev->tx_duty_cycle = duty_cycle;
	ene_tx_set_carrier(dev);
	return 0;
}