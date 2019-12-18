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
struct ab8500_usb {void* v_musb; int /*<<< orphan*/  dev; void* v_ulpi; void* v_ape; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 void* devm_regulator_get (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int ab8500_usb_regulator_get(struct ab8500_usb *ab)
{
	int err;

	ab->v_ape = devm_regulator_get(ab->dev, "v-ape");
	if (IS_ERR(ab->v_ape)) {
		dev_err(ab->dev, "Could not get v-ape supply\n");
		err = PTR_ERR(ab->v_ape);
		return err;
	}

	ab->v_ulpi = devm_regulator_get(ab->dev, "vddulpivio18");
	if (IS_ERR(ab->v_ulpi)) {
		dev_err(ab->dev, "Could not get vddulpivio18 supply\n");
		err = PTR_ERR(ab->v_ulpi);
		return err;
	}

	ab->v_musb = devm_regulator_get(ab->dev, "musb_1v8");
	if (IS_ERR(ab->v_musb)) {
		dev_err(ab->dev, "Could not get musb_1v8 supply\n");
		err = PTR_ERR(ab->v_musb);
		return err;
	}

	return 0;
}