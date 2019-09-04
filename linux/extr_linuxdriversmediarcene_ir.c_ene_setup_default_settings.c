#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ene_device {int tx_period; int tx_duty_cycle; int transmitter_mask; TYPE_1__* rdev; int /*<<< orphan*/  learning_mode_enabled; } ;
struct TYPE_2__ {int /*<<< orphan*/  timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  US_TO_NS (int) ; 
 int /*<<< orphan*/  learning_mode_force ; 

__attribute__((used)) static void ene_setup_default_settings(struct ene_device *dev)
{
	dev->tx_period = 32;
	dev->tx_duty_cycle = 50; /*%*/
	dev->transmitter_mask = 0x03;
	dev->learning_mode_enabled = learning_mode_force;

	/* Set reasonable default timeout */
	dev->rdev->timeout = US_TO_NS(150000);
}