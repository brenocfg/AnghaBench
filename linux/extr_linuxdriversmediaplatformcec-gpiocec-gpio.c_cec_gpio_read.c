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
struct cec_gpio {int /*<<< orphan*/  cec_gpio; scalar_t__ cec_is_low; } ;
struct cec_adapter {int dummy; } ;

/* Variables and functions */
 struct cec_gpio* cec_get_drvdata (struct cec_adapter*) ; 
 int gpiod_get_value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool cec_gpio_read(struct cec_adapter *adap)
{
	struct cec_gpio *cec = cec_get_drvdata(adap);

	if (cec->cec_is_low)
		return false;
	return gpiod_get_value(cec->cec_gpio);
}