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
typedef  scalar_t__ u16 ;
struct secocec_data {struct device* cec_adap; int /*<<< orphan*/  notifier; int /*<<< orphan*/  irq; struct device* dev; struct platform_device* pdev; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRA_SMB_BASE_ADDR ; 
 int CEC_CAP_CONNECTOR_INFO ; 
 int CEC_CAP_DEFAULTS ; 
 int EINVAL ; 
 int EIO ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_RISING ; 
 scalar_t__ IS_ERR (struct device*) ; 
 int PTR_ERR (struct device*) ; 
 scalar_t__ SECOCEC_LATEST_FW ; 
 int /*<<< orphan*/  SECOCEC_MAX_ADDRS ; 
 int /*<<< orphan*/  SECOCEC_VERSION ; 
 struct device* cec_allocate_adapter (int /*<<< orphan*/ *,struct secocec_data*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cec_delete_adapter (struct device*) ; 
 int /*<<< orphan*/  cec_notifier_cec_adap_register (struct device*,char const*,struct device*) ; 
 int /*<<< orphan*/  cec_notifier_cec_adap_unregister (int /*<<< orphan*/ ) ; 
 int cec_register_adapter (struct device*,struct device*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct secocec_data*) ; 
 struct secocec_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct secocec_data*) ; 
 int /*<<< orphan*/  has_acpi_companion (struct device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct secocec_data*) ; 
 int /*<<< orphan*/  request_muxed_region (int /*<<< orphan*/ ,int,char*) ; 
 int secocec_acpi_probe (struct secocec_data*) ; 
 int /*<<< orphan*/  secocec_cec_adap_ops ; 
 struct device* secocec_cec_find_hdmi_dev (struct device*,char const**) ; 
 int secocec_ir_probe (struct secocec_data*) ; 
 int /*<<< orphan*/  secocec_irq_handler ; 
 int smb_rd16 (int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static int secocec_probe(struct platform_device *pdev)
{
	struct secocec_data *secocec;
	struct device *dev = &pdev->dev;
	struct device *hdmi_dev;
	const char *conn = NULL;
	int ret;
	u16 val;

	hdmi_dev = secocec_cec_find_hdmi_dev(&pdev->dev, &conn);
	if (IS_ERR(hdmi_dev))
		return PTR_ERR(hdmi_dev);

	secocec = devm_kzalloc(dev, sizeof(*secocec), GFP_KERNEL);
	if (!secocec)
		return -ENOMEM;

	dev_set_drvdata(dev, secocec);

	/* Request SMBus regions */
	if (!request_muxed_region(BRA_SMB_BASE_ADDR, 7, "CEC00001")) {
		dev_err(dev, "Request memory region failed");
		return -ENXIO;
	}

	secocec->pdev = pdev;
	secocec->dev = dev;

	if (!has_acpi_companion(dev)) {
		dev_dbg(dev, "Cannot find any ACPI companion");
		ret = -ENODEV;
		goto err;
	}

	ret = secocec_acpi_probe(secocec);
	if (ret) {
		dev_err(dev, "Cannot assign gpio to IRQ");
		ret = -ENODEV;
		goto err;
	}

	/* Firmware version check */
	ret = smb_rd16(SECOCEC_VERSION, &val);
	if (ret) {
		dev_err(dev, "Cannot check fw version");
		goto err;
	}
	if (val < SECOCEC_LATEST_FW) {
		dev_err(dev, "CEC Firmware not supported (v.%04x). Use ver > v.%04x",
			val, SECOCEC_LATEST_FW);
		ret = -EINVAL;
		goto err;
	}

	ret = devm_request_threaded_irq(dev,
					secocec->irq,
					NULL,
					secocec_irq_handler,
					IRQF_TRIGGER_RISING | IRQF_ONESHOT,
					dev_name(&pdev->dev), secocec);

	if (ret) {
		dev_err(dev, "Cannot request IRQ %d", secocec->irq);
		ret = -EIO;
		goto err;
	}

	/* Allocate CEC adapter */
	secocec->cec_adap = cec_allocate_adapter(&secocec_cec_adap_ops,
						 secocec,
						 dev_name(dev),
						 CEC_CAP_DEFAULTS |
						 CEC_CAP_CONNECTOR_INFO,
						 SECOCEC_MAX_ADDRS);

	if (IS_ERR(secocec->cec_adap)) {
		ret = PTR_ERR(secocec->cec_adap);
		goto err;
	}

	secocec->notifier = cec_notifier_cec_adap_register(hdmi_dev, conn,
							   secocec->cec_adap);
	if (!secocec->notifier) {
		ret = -ENOMEM;
		goto err_delete_adapter;
	}

	ret = cec_register_adapter(secocec->cec_adap, dev);
	if (ret)
		goto err_notifier;

	ret = secocec_ir_probe(secocec);
	if (ret)
		goto err_notifier;

	platform_set_drvdata(pdev, secocec);

	dev_dbg(dev, "Device registered");

	return ret;

err_notifier:
	cec_notifier_cec_adap_unregister(secocec->notifier);
err_delete_adapter:
	cec_delete_adapter(secocec->cec_adap);
err:
	dev_err(dev, "%s device probe failed\n", dev_name(dev));

	return ret;
}