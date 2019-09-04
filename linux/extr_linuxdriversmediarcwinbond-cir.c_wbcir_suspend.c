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
struct wbcir_data {int /*<<< orphan*/  led; } ;
struct pnp_dev {int dummy; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 int /*<<< orphan*/  led_classdev_suspend (int /*<<< orphan*/ *) ; 
 struct wbcir_data* pnp_get_drvdata (struct pnp_dev*) ; 
 int /*<<< orphan*/  wbcir_shutdown (struct pnp_dev*) ; 

__attribute__((used)) static int
wbcir_suspend(struct pnp_dev *device, pm_message_t state)
{
	struct wbcir_data *data = pnp_get_drvdata(device);
	led_classdev_suspend(&data->led);
	wbcir_shutdown(device);
	return 0;
}