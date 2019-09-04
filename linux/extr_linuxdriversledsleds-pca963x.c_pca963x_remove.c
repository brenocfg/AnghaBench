#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pca963x {TYPE_2__* leds; TYPE_1__* chipdef; } ;
struct i2c_client {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  led_cdev; } ;
struct TYPE_3__ {int n_leds; } ;

/* Variables and functions */
 struct pca963x* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  led_classdev_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pca963x_remove(struct i2c_client *client)
{
	struct pca963x *pca963x = i2c_get_clientdata(client);
	int i;

	for (i = 0; i < pca963x->chipdef->n_leds; i++)
		led_classdev_unregister(&pca963x->leds[i].led_cdev);

	return 0;
}