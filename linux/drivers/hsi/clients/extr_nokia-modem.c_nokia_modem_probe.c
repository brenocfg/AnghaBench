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
struct nokia_modem_device {int nokia_modem_rst_ind_irq; int /*<<< orphan*/  nokia_modem_rst_ind_tasklet; TYPE_2__* ssi_protocol; TYPE_1__* cmt_speech; struct device* device; } ;
struct hsi_port {int dummy; } ;
struct hsi_client {int /*<<< orphan*/  rx_cfg; int /*<<< orphan*/  tx_cfg; } ;
struct hsi_board_info {char* name; int /*<<< orphan*/ * archdata; int /*<<< orphan*/ * platform_data; int /*<<< orphan*/  rx_cfg; int /*<<< orphan*/  tx_cfg; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct TYPE_4__ {int /*<<< orphan*/  device; } ;
struct TYPE_3__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ENXIO ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct nokia_modem_device*) ; 
 int device_attach (int /*<<< orphan*/ *) ; 
 struct nokia_modem_device* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int,char*,struct nokia_modem_device*) ; 
 int /*<<< orphan*/  disable_irq_wake (int) ; 
 int /*<<< orphan*/  do_nokia_modem_rst_ind_tasklet ; 
 int /*<<< orphan*/  enable_irq_wake (int) ; 
 struct hsi_port* hsi_get_port (struct hsi_client*) ; 
 void* hsi_new_client (struct hsi_port*,struct hsi_board_info*) ; 
 int /*<<< orphan*/  hsi_remove_client (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int irq_get_trigger_type (int) ; 
 int irq_of_parse_and_map (struct device_node*,int /*<<< orphan*/ ) ; 
 int nokia_modem_gpio_probe (struct device*) ; 
 int /*<<< orphan*/  nokia_modem_gpio_unexport (struct device*) ; 
 int /*<<< orphan*/  nokia_modem_rst_ind_isr ; 
 scalar_t__ pm ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 struct hsi_client* to_hsi_client (struct device*) ; 

__attribute__((used)) static int nokia_modem_probe(struct device *dev)
{
	struct device_node *np;
	struct nokia_modem_device *modem;
	struct hsi_client *cl = to_hsi_client(dev);
	struct hsi_port *port = hsi_get_port(cl);
	int irq, pflags, err;
	struct hsi_board_info ssip;
	struct hsi_board_info cmtspeech;

	np = dev->of_node;
	if (!np) {
		dev_err(dev, "device tree node not found\n");
		return -ENXIO;
	}

	modem = devm_kzalloc(dev, sizeof(*modem), GFP_KERNEL);
	if (!modem)
		return -ENOMEM;

	dev_set_drvdata(dev, modem);
	modem->device = dev;

	irq = irq_of_parse_and_map(np, 0);
	if (!irq) {
		dev_err(dev, "Invalid rst_ind interrupt (%d)\n", irq);
		return -EINVAL;
	}
	modem->nokia_modem_rst_ind_irq = irq;
	pflags = irq_get_trigger_type(irq);

	tasklet_init(&modem->nokia_modem_rst_ind_tasklet,
			do_nokia_modem_rst_ind_tasklet, (unsigned long)modem);
	err = devm_request_irq(dev, irq, nokia_modem_rst_ind_isr,
				pflags, "modem_rst_ind", modem);
	if (err < 0) {
		dev_err(dev, "Request rst_ind irq(%d) failed (flags %d)\n",
								irq, pflags);
		return err;
	}
	enable_irq_wake(irq);

	if (pm) {
		err = nokia_modem_gpio_probe(dev);
		if (err < 0) {
			dev_err(dev, "Could not probe GPIOs\n");
			goto error1;
		}
	}

	ssip.name = "ssi-protocol";
	ssip.tx_cfg = cl->tx_cfg;
	ssip.rx_cfg = cl->rx_cfg;
	ssip.platform_data = NULL;
	ssip.archdata = NULL;

	modem->ssi_protocol = hsi_new_client(port, &ssip);
	if (!modem->ssi_protocol) {
		dev_err(dev, "Could not register ssi-protocol device\n");
		err = -ENOMEM;
		goto error2;
	}

	err = device_attach(&modem->ssi_protocol->device);
	if (err == 0) {
		dev_dbg(dev, "Missing ssi-protocol driver\n");
		err = -EPROBE_DEFER;
		goto error3;
	} else if (err < 0) {
		dev_err(dev, "Could not load ssi-protocol driver (%d)\n", err);
		goto error3;
	}

	cmtspeech.name = "cmt-speech";
	cmtspeech.tx_cfg = cl->tx_cfg;
	cmtspeech.rx_cfg = cl->rx_cfg;
	cmtspeech.platform_data = NULL;
	cmtspeech.archdata = NULL;

	modem->cmt_speech = hsi_new_client(port, &cmtspeech);
	if (!modem->cmt_speech) {
		dev_err(dev, "Could not register cmt-speech device\n");
		err = -ENOMEM;
		goto error3;
	}

	err = device_attach(&modem->cmt_speech->device);
	if (err == 0) {
		dev_dbg(dev, "Missing cmt-speech driver\n");
		err = -EPROBE_DEFER;
		goto error4;
	} else if (err < 0) {
		dev_err(dev, "Could not load cmt-speech driver (%d)\n", err);
		goto error4;
	}

	dev_info(dev, "Registered Nokia HSI modem\n");

	return 0;

error4:
	hsi_remove_client(&modem->cmt_speech->device, NULL);
error3:
	hsi_remove_client(&modem->ssi_protocol->device, NULL);
error2:
	nokia_modem_gpio_unexport(dev);
error1:
	disable_irq_wake(modem->nokia_modem_rst_ind_irq);
	tasklet_kill(&modem->nokia_modem_rst_ind_tasklet);

	return err;
}