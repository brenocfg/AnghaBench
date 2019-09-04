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
struct dln2_gpio_pin_val {scalar_t__ pin; int value; } ;
struct dln2_gpio_pin {scalar_t__ pin; } ;
struct dln2_gpio {int /*<<< orphan*/  pdev; } ;
typedef  int /*<<< orphan*/  rsp ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int EPROTO ; 
 scalar_t__ cpu_to_le16 (unsigned int) ; 
 int dln2_transfer (int /*<<< orphan*/ ,int,struct dln2_gpio_pin*,int,struct dln2_gpio_pin_val*,int*) ; 

__attribute__((used)) static int dln2_gpio_pin_val(struct dln2_gpio *dln2, int cmd, unsigned int pin)
{
	int ret;
	struct dln2_gpio_pin req = {
		.pin = cpu_to_le16(pin),
	};
	struct dln2_gpio_pin_val rsp;
	int len = sizeof(rsp);

	ret = dln2_transfer(dln2->pdev, cmd, &req, sizeof(req), &rsp, &len);
	if (ret < 0)
		return ret;
	if (len < sizeof(rsp) || req.pin != rsp.pin)
		return -EPROTO;

	return rsp.value;
}