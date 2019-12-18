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
struct cec_gpio {int /*<<< orphan*/  cec_irq; } ;
struct cec_adapter {int dummy; } ;

/* Variables and functions */
 struct cec_gpio* cec_get_drvdata (struct cec_adapter*) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cec_gpio_disable_irq(struct cec_adapter *adap)
{
	struct cec_gpio *cec = cec_get_drvdata(adap);

	disable_irq(cec->cec_irq);
}