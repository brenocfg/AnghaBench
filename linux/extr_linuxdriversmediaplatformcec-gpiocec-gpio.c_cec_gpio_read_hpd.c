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
struct cec_gpio {int /*<<< orphan*/  hpd_gpio; } ;
struct cec_adapter {int dummy; } ;

/* Variables and functions */
 int ENOTTY ; 
 struct cec_gpio* cec_get_drvdata (struct cec_adapter*) ; 
 int gpiod_get_value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cec_gpio_read_hpd(struct cec_adapter *adap)
{
	struct cec_gpio *cec = cec_get_drvdata(adap);

	if (!cec->hpd_gpio)
		return -ENOTTY;
	return gpiod_get_value(cec->hpd_gpio);
}