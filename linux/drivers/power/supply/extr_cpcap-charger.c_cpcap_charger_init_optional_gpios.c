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
struct cpcap_charger_ddata {int /*<<< orphan*/ ** gpio; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * devm_gpiod_get_index (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cpcap_charger_init_optional_gpios(struct cpcap_charger_ddata *ddata)
{
	int i;

	for (i = 0; i < 2; i++) {
		ddata->gpio[i] = devm_gpiod_get_index(ddata->dev, "mode",
						      i, GPIOD_OUT_HIGH);
		if (IS_ERR(ddata->gpio[i])) {
			dev_info(ddata->dev, "no mode change GPIO%i: %li\n",
				 i, PTR_ERR(ddata->gpio[i]));
			ddata->gpio[i] = NULL;
		}
	}
}