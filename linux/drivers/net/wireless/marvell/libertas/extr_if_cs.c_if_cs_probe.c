#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pcmcia_device {int config_flags; int /*<<< orphan*/  dev; int /*<<< orphan*/  card_id; int /*<<< orphan*/  manf_id; TYPE_1__** resource; int /*<<< orphan*/  irq; struct if_cs_card* priv; } ;
struct lbs_private {int /*<<< orphan*/ * reset_deep_sleep_wakeup; int /*<<< orphan*/ * exit_deep_sleep; int /*<<< orphan*/ * enter_deep_sleep; int /*<<< orphan*/  hw_host_to_card; struct if_cs_card* card; } ;
struct if_cs_card {int align_regs; scalar_t__ model; int /*<<< orphan*/  iobase; struct lbs_private* priv; struct pcmcia_device* p_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int CONF_AUTO_SET_IO ; 
 int CONF_ENABLE_IRQ ; 
 int EIO ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int IF_CS_CF8305_B1_REV ; 
 unsigned int IF_CS_CF8381_B3_REV ; 
 unsigned int IF_CS_CF8385_B1_REV ; 
 int /*<<< orphan*/  IF_CS_PRODUCT_ID ; 
 scalar_t__ IS_ERR (struct lbs_private*) ; 
 scalar_t__ MODEL_8305 ; 
 scalar_t__ MODEL_8381 ; 
 scalar_t__ MODEL_8385 ; 
 scalar_t__ MODEL_UNKNOWN ; 
 int PTR_ERR (struct lbs_private*) ; 
 int /*<<< orphan*/  fw_table ; 
 scalar_t__ get_model (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_cs_host_to_card ; 
 int /*<<< orphan*/  if_cs_ioprobe ; 
 int /*<<< orphan*/  if_cs_prog_firmware ; 
 unsigned int if_cs_read8 (struct if_cs_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioport_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioport_unmap (int /*<<< orphan*/ ) ; 
 struct if_cs_card* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct lbs_private* lbs_add_card (struct if_cs_card*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lbs_deb_cs (char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int lbs_get_firmware_async (struct lbs_private*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_remove_card (struct lbs_private*) ; 
 int /*<<< orphan*/  pcmcia_disable_device (struct pcmcia_device*) ; 
 int pcmcia_enable_device (struct pcmcia_device*) ; 
 scalar_t__ pcmcia_loop_config (struct pcmcia_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  resource_size (TYPE_1__*) ; 

__attribute__((used)) static int if_cs_probe(struct pcmcia_device *p_dev)
{
	int ret = -ENOMEM;
	unsigned int prod_id;
	struct lbs_private *priv;
	struct if_cs_card *card;

	card = kzalloc(sizeof(struct if_cs_card), GFP_KERNEL);
	if (!card)
		goto out;

	card->p_dev = p_dev;
	p_dev->priv = card;

	p_dev->config_flags |= CONF_ENABLE_IRQ | CONF_AUTO_SET_IO;

	if (pcmcia_loop_config(p_dev, if_cs_ioprobe, NULL)) {
		pr_err("error in pcmcia_loop_config\n");
		goto out1;
	}

	/*
	 * Allocate an interrupt line.  Note that this does not assign
	 * a handler to the interrupt, unless the 'Handler' member of
	 * the irq structure is initialized.
	 */
	if (!p_dev->irq)
		goto out1;

	/* Initialize io access */
	card->iobase = ioport_map(p_dev->resource[0]->start,
				resource_size(p_dev->resource[0]));
	if (!card->iobase) {
		pr_err("error in ioport_map\n");
		ret = -EIO;
		goto out1;
	}

	ret = pcmcia_enable_device(p_dev);
	if (ret) {
		pr_err("error in pcmcia_enable_device\n");
		goto out2;
	}

	/* Finally, report what we've done */
	lbs_deb_cs("irq %d, io %pR", p_dev->irq, p_dev->resource[0]);

	/*
	 * Most of the libertas cards can do unaligned register access, but some
	 * weird ones cannot. That's especially true for the CF8305 card.
	 */
	card->align_regs = false;

	card->model = get_model(p_dev->manf_id, p_dev->card_id);
	if (card->model == MODEL_UNKNOWN) {
		pr_err("unsupported manf_id 0x%04x / card_id 0x%04x\n",
		       p_dev->manf_id, p_dev->card_id);
		ret = -ENODEV;
		goto out2;
	}

	/* Check if we have a current silicon */
	prod_id = if_cs_read8(card, IF_CS_PRODUCT_ID);
	if (card->model == MODEL_8305) {
		card->align_regs = true;
		if (prod_id < IF_CS_CF8305_B1_REV) {
			pr_err("8305 rev B0 and older are not supported\n");
			ret = -ENODEV;
			goto out2;
		}
	}

	if ((card->model == MODEL_8381) && prod_id < IF_CS_CF8381_B3_REV) {
		pr_err("8381 rev B2 and older are not supported\n");
		ret = -ENODEV;
		goto out2;
	}

	if ((card->model == MODEL_8385) && prod_id < IF_CS_CF8385_B1_REV) {
		pr_err("8385 rev B0 and older are not supported\n");
		ret = -ENODEV;
		goto out2;
	}

	/* Make this card known to the libertas driver */
	priv = lbs_add_card(card, &p_dev->dev);
	if (IS_ERR(priv)) {
		ret = PTR_ERR(priv);
		goto out2;
	}

	/* Set up fields in lbs_private */
	card->priv = priv;
	priv->card = card;
	priv->hw_host_to_card = if_cs_host_to_card;
	priv->enter_deep_sleep = NULL;
	priv->exit_deep_sleep = NULL;
	priv->reset_deep_sleep_wakeup = NULL;

	/* Get firmware */
	ret = lbs_get_firmware_async(priv, &p_dev->dev, card->model, fw_table,
				     if_cs_prog_firmware);
	if (ret) {
		pr_err("failed to find firmware (%d)\n", ret);
		goto out3;
	}

	goto out;

out3:
	lbs_remove_card(priv);
out2:
	ioport_unmap(card->iobase);
out1:
	pcmcia_disable_device(p_dev);
out:
	return ret;
}