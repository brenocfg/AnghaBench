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
struct dln2_gpio_pin {int /*<<< orphan*/  pin; } ;
struct dln2_gpio {int /*<<< orphan*/  pdev; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le16 (unsigned int) ; 
 int dln2_transfer_tx (int /*<<< orphan*/ ,int,struct dln2_gpio_pin*,int) ; 

__attribute__((used)) static int dln2_gpio_pin_cmd(struct dln2_gpio *dln2, int cmd, unsigned pin)
{
	struct dln2_gpio_pin req = {
		.pin = cpu_to_le16(pin),
	};

	return dln2_transfer_tx(dln2->pdev, cmd, &req, sizeof(req));
}