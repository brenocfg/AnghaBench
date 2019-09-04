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
struct platform_device {int dummy; } ;
struct omap_ssi_port {int wake_irq; int /*<<< orphan*/  wake_gpio; } ;
struct hsi_port {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_FALLING ; 
 int IRQF_TRIGGER_RISING ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct hsi_port*) ; 
 int enable_irq_wake (int) ; 
 int gpiod_to_irq (int /*<<< orphan*/ ) ; 
 struct omap_ssi_port* hsi_port_drvdata (struct hsi_port*) ; 
 int /*<<< orphan*/  ssi_wake_thread ; 

__attribute__((used)) static int ssi_wake_irq(struct hsi_port *port, struct platform_device *pd)
{
	struct omap_ssi_port *omap_port = hsi_port_drvdata(port);
	int cawake_irq;
	int err;

	if (!omap_port->wake_gpio) {
		omap_port->wake_irq = -1;
		return 0;
	}

	cawake_irq = gpiod_to_irq(omap_port->wake_gpio);
	omap_port->wake_irq = cawake_irq;

	err = devm_request_threaded_irq(&port->device, cawake_irq, NULL,
		ssi_wake_thread,
		IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
		"SSI cawake", port);
	if (err < 0)
		dev_err(&port->device, "Request Wake in IRQ %d failed %d\n",
						cawake_irq, err);
	err = enable_irq_wake(cawake_irq);
	if (err < 0)
		dev_err(&port->device, "Enable wake on the wakeline in irq %d failed %d\n",
			cawake_irq, err);

	return err;
}