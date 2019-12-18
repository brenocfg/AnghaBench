#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pcmcia_device {int config_flags; int irq; char** prod_id; struct pcan_pccard* priv; int /*<<< orphan*/  dev; TYPE_1__** resource; } ;
struct pcan_pccard {int /*<<< orphan*/  ioport_addr; int /*<<< orphan*/  led_timer; int /*<<< orphan*/  chan_count; void* fw_minor; void* fw_major; struct pcmcia_device* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int CONF_AUTO_SET_IO ; 
 int CONF_ENABLE_IRQ ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  PCC_FW_MAJOR ; 
 int /*<<< orphan*/  PCC_FW_MINOR ; 
 int /*<<< orphan*/  PCC_NAME ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char*,void*,void*) ; 
 int /*<<< orphan*/  ioport_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioport_unmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct pcan_pccard*) ; 
 struct pcan_pccard* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcan_add_channels (struct pcan_pccard*) ; 
 int /*<<< orphan*/  pcan_conf_check ; 
 int /*<<< orphan*/  pcan_free_channels (struct pcan_pccard*) ; 
 int /*<<< orphan*/  pcan_isr ; 
 int /*<<< orphan*/  pcan_led_timer ; 
 void* pcan_read_reg (struct pcan_pccard*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcan_set_can_power (struct pcan_pccard*,int) ; 
 int /*<<< orphan*/  pcmcia_disable_device (struct pcmcia_device*) ; 
 int pcmcia_enable_device (struct pcmcia_device*) ; 
 int pcmcia_loop_config (struct pcmcia_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int request_irq (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pcan_pccard*) ; 
 int /*<<< orphan*/  resource_size (TYPE_1__*) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcan_probe(struct pcmcia_device *pdev)
{
	struct pcan_pccard *card;
	int err;

	pdev->config_flags |= CONF_ENABLE_IRQ | CONF_AUTO_SET_IO;

	err = pcmcia_loop_config(pdev, pcan_conf_check, NULL);
	if (err) {
		dev_err(&pdev->dev, "pcmcia_loop_config() error %d\n", err);
		goto probe_err_1;
	}

	if (!pdev->irq) {
		dev_err(&pdev->dev, "no irq assigned\n");
		err = -ENODEV;
		goto probe_err_1;
	}

	err = pcmcia_enable_device(pdev);
	if (err) {
		dev_err(&pdev->dev, "pcmcia_enable_device failed err=%d\n",
			err);
		goto probe_err_1;
	}

	card = kzalloc(sizeof(struct pcan_pccard), GFP_KERNEL);
	if (!card) {
		err = -ENOMEM;
		goto probe_err_2;
	}

	card->pdev = pdev;
	pdev->priv = card;

	/* sja1000 api uses iomem */
	card->ioport_addr = ioport_map(pdev->resource[0]->start,
					resource_size(pdev->resource[0]));
	if (!card->ioport_addr) {
		dev_err(&pdev->dev, "couldn't map io port into io memory\n");
		err = -ENOMEM;
		goto probe_err_3;
	}
	card->fw_major = pcan_read_reg(card, PCC_FW_MAJOR);
	card->fw_minor = pcan_read_reg(card, PCC_FW_MINOR);

	/* display board name and firware version */
	dev_info(&pdev->dev, "PEAK-System pcmcia card %s fw %d.%d\n",
		pdev->prod_id[1] ? pdev->prod_id[1] : "PCAN-PC Card",
		card->fw_major, card->fw_minor);

	/* detect available channels */
	pcan_add_channels(card);
	if (!card->chan_count) {
		err = -ENOMEM;
		goto probe_err_4;
	}

	/* init the timer which controls the leds */
	timer_setup(&card->led_timer, pcan_led_timer, 0);

	/* request the given irq */
	err = request_irq(pdev->irq, &pcan_isr, IRQF_SHARED, PCC_NAME, card);
	if (err) {
		dev_err(&pdev->dev, "couldn't request irq%d\n", pdev->irq);
		goto probe_err_5;
	}

	/* power on the connectors */
	pcan_set_can_power(card, 1);

	return 0;

probe_err_5:
	/* unregister can devices from network */
	pcan_free_channels(card);

probe_err_4:
	ioport_unmap(card->ioport_addr);

probe_err_3:
	kfree(card);
	pdev->priv = NULL;

probe_err_2:
	pcmcia_disable_device(pdev);

probe_err_1:
	return err;
}