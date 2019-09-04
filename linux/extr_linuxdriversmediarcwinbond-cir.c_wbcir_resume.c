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
struct wbcir_data {int /*<<< orphan*/  led; int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct pnp_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ir_raw_event_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  led_classdev_resume (int /*<<< orphan*/ *) ; 
 struct wbcir_data* pnp_get_drvdata (struct pnp_dev*) ; 
 int /*<<< orphan*/  wbcir_init_hw (struct wbcir_data*) ; 

__attribute__((used)) static int
wbcir_resume(struct pnp_dev *device)
{
	struct wbcir_data *data = pnp_get_drvdata(device);

	wbcir_init_hw(data);
	ir_raw_event_reset(data->dev);
	enable_irq(data->irq);
	led_classdev_resume(&data->led);

	return 0;
}