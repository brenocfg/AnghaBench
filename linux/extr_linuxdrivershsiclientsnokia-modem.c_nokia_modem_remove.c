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
struct nokia_modem_device {int /*<<< orphan*/  nokia_modem_rst_ind_tasklet; int /*<<< orphan*/  nokia_modem_rst_ind_irq; TYPE_1__* ssi_protocol; TYPE_2__* cmt_speech; } ;
struct device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  device; } ;
struct TYPE_3__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 struct nokia_modem_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_irq_wake (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hsi_remove_client (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nokia_modem_gpio_unexport (struct device*) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nokia_modem_remove(struct device *dev)
{
	struct nokia_modem_device *modem = dev_get_drvdata(dev);

	if (!modem)
		return 0;

	if (modem->cmt_speech) {
		hsi_remove_client(&modem->cmt_speech->device, NULL);
		modem->cmt_speech = NULL;
	}

	if (modem->ssi_protocol) {
		hsi_remove_client(&modem->ssi_protocol->device, NULL);
		modem->ssi_protocol = NULL;
	}

	nokia_modem_gpio_unexport(dev);
	dev_set_drvdata(dev, NULL);
	disable_irq_wake(modem->nokia_modem_rst_ind_irq);
	tasklet_kill(&modem->nokia_modem_rst_ind_tasklet);

	return 0;
}