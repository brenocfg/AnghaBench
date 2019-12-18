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
struct cec_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cec_gpio_disable_irq (struct cec_adapter*) ; 

__attribute__((used)) static void cec_gpio_free(struct cec_adapter *adap)
{
	cec_gpio_disable_irq(adap);
}