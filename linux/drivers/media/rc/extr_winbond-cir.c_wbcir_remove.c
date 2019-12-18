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
struct wbcir_data {scalar_t__ sbase; scalar_t__ ebase; scalar_t__ wbase; int /*<<< orphan*/  led; int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;
struct pnp_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EHFUNC_IOMEM_LEN ; 
 int /*<<< orphan*/  LED_OFF ; 
 int /*<<< orphan*/  SP_IOMEM_LEN ; 
 int /*<<< orphan*/  WAKEUP_IOMEM_LEN ; 
 int /*<<< orphan*/  WBCIR_IRQ_NONE ; 
 scalar_t__ WBCIR_REG_WCEIR_CTL ; 
 scalar_t__ WBCIR_REG_WCEIR_EV_EN ; 
 scalar_t__ WBCIR_REG_WCEIR_STS ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct pnp_dev*) ; 
 int /*<<< orphan*/  kfree (struct wbcir_data*) ; 
 int /*<<< orphan*/  led_classdev_unregister (int /*<<< orphan*/ *) ; 
 struct wbcir_data* pnp_get_drvdata (struct pnp_dev*) ; 
 int /*<<< orphan*/  pnp_set_drvdata (struct pnp_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rc_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_region (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wbcir_led_brightness_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wbcir_set_bits (scalar_t__,int,int) ; 
 int /*<<< orphan*/  wbcir_set_irqmask (struct wbcir_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
wbcir_remove(struct pnp_dev *device)
{
	struct wbcir_data *data = pnp_get_drvdata(device);

	/* Disable interrupts */
	wbcir_set_irqmask(data, WBCIR_IRQ_NONE);
	free_irq(data->irq, device);

	/* Clear status bits NEC_REP, BUFF, MSG_END, MATCH */
	wbcir_set_bits(data->wbase + WBCIR_REG_WCEIR_STS, 0x17, 0x17);

	/* Clear CEIR_EN */
	wbcir_set_bits(data->wbase + WBCIR_REG_WCEIR_CTL, 0x00, 0x01);

	/* Clear BUFF_EN, END_EN, MATCH_EN */
	wbcir_set_bits(data->wbase + WBCIR_REG_WCEIR_EV_EN, 0x00, 0x07);

	rc_unregister_device(data->dev);

	led_classdev_unregister(&data->led);

	/* This is ok since &data->led isn't actually used */
	wbcir_led_brightness_set(&data->led, LED_OFF);

	release_region(data->wbase, WAKEUP_IOMEM_LEN);
	release_region(data->ebase, EHFUNC_IOMEM_LEN);
	release_region(data->sbase, SP_IOMEM_LEN);

	kfree(data);

	pnp_set_drvdata(device, NULL);
}