#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct dw_hdmi_cec_data {int /*<<< orphan*/  hdmi; int /*<<< orphan*/  ops; int /*<<< orphan*/  irq; } ;
struct dw_hdmi_cec {int /*<<< orphan*/  notify; TYPE_2__* adap; int /*<<< orphan*/  irq; int /*<<< orphan*/  hdmi; int /*<<< orphan*/  ops; } ;
struct TYPE_14__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int CEC_CAP_CONNECTOR_INFO ; 
 int CEC_CAP_DEFAULTS ; 
 int /*<<< orphan*/  CEC_MAX_LOG_ADDRS ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HDMI_CEC_MASK ; 
 int /*<<< orphan*/  HDMI_CEC_POLARITY ; 
 int /*<<< orphan*/  HDMI_CEC_TX_CNT ; 
 int /*<<< orphan*/  HDMI_IH_MUTE_CEC_STAT0 ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ IS_ERR (TYPE_2__*) ; 
 int PTR_ERR (TYPE_2__*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 TYPE_2__* cec_allocate_adapter (int /*<<< orphan*/ *,struct dw_hdmi_cec*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cec_delete_adapter (TYPE_2__*) ; 
 int /*<<< orphan*/  cec_notifier_cec_adap_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  cec_notifier_cec_adap_unregister (int /*<<< orphan*/ ) ; 
 int cec_register_adapter (TYPE_2__*,int /*<<< orphan*/ ) ; 
 struct dw_hdmi_cec_data* dev_get_platdata (TYPE_1__*) ; 
 int devm_add_action (TYPE_1__*,int /*<<< orphan*/ ,struct dw_hdmi_cec*) ; 
 struct dw_hdmi_cec* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_remove_action (TYPE_1__*,int /*<<< orphan*/ ,struct dw_hdmi_cec*) ; 
 int devm_request_threaded_irq (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_2__*) ; 
 int /*<<< orphan*/  dw_hdmi_cec_del ; 
 int /*<<< orphan*/  dw_hdmi_cec_hardirq ; 
 int /*<<< orphan*/  dw_hdmi_cec_ops ; 
 int /*<<< orphan*/  dw_hdmi_cec_thread ; 
 int /*<<< orphan*/  dw_hdmi_write (struct dw_hdmi_cec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct dw_hdmi_cec*) ; 

__attribute__((used)) static int dw_hdmi_cec_probe(struct platform_device *pdev)
{
	struct dw_hdmi_cec_data *data = dev_get_platdata(&pdev->dev);
	struct dw_hdmi_cec *cec;
	int ret;

	if (!data)
		return -ENXIO;

	/*
	 * Our device is just a convenience - we want to link to the real
	 * hardware device here, so that userspace can see the association
	 * between the HDMI hardware and its associated CEC chardev.
	 */
	cec = devm_kzalloc(&pdev->dev, sizeof(*cec), GFP_KERNEL);
	if (!cec)
		return -ENOMEM;

	cec->irq = data->irq;
	cec->ops = data->ops;
	cec->hdmi = data->hdmi;

	platform_set_drvdata(pdev, cec);

	dw_hdmi_write(cec, 0, HDMI_CEC_TX_CNT);
	dw_hdmi_write(cec, ~0, HDMI_CEC_MASK);
	dw_hdmi_write(cec, ~0, HDMI_IH_MUTE_CEC_STAT0);
	dw_hdmi_write(cec, 0, HDMI_CEC_POLARITY);

	cec->adap = cec_allocate_adapter(&dw_hdmi_cec_ops, cec, "dw_hdmi",
					 CEC_CAP_DEFAULTS |
					 CEC_CAP_CONNECTOR_INFO,
					 CEC_MAX_LOG_ADDRS);
	if (IS_ERR(cec->adap))
		return PTR_ERR(cec->adap);

	/* override the module pointer */
	cec->adap->owner = THIS_MODULE;

	ret = devm_add_action(&pdev->dev, dw_hdmi_cec_del, cec);
	if (ret) {
		cec_delete_adapter(cec->adap);
		return ret;
	}

	ret = devm_request_threaded_irq(&pdev->dev, cec->irq,
					dw_hdmi_cec_hardirq,
					dw_hdmi_cec_thread, IRQF_SHARED,
					"dw-hdmi-cec", cec->adap);
	if (ret < 0)
		return ret;

	cec->notify = cec_notifier_cec_adap_register(pdev->dev.parent,
						     NULL, cec->adap);
	if (!cec->notify)
		return -ENOMEM;

	ret = cec_register_adapter(cec->adap, pdev->dev.parent);
	if (ret < 0) {
		cec_notifier_cec_adap_unregister(cec->notify);
		return ret;
	}

	/*
	 * CEC documentation says we must not call cec_delete_adapter
	 * after a successful call to cec_register_adapter().
	 */
	devm_remove_action(&pdev->dev, dw_hdmi_cec_del, cec);

	return 0;
}