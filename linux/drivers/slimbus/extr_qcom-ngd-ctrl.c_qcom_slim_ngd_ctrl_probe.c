#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_6__ {int /*<<< orphan*/  qmi_comp; } ;
struct TYPE_5__ {int /*<<< orphan*/ * wakeup; int /*<<< orphan*/  xfer_msg; int /*<<< orphan*/  enable_stream; int /*<<< orphan*/  get_laddr; int /*<<< orphan*/  clkgear; TYPE_1__* a_framer; } ;
struct TYPE_4__ {int rootfreq; int superfreq; } ;
struct qcom_slim_ngd_ctrl {TYPE_3__ qmi; int /*<<< orphan*/  reconf; int /*<<< orphan*/  tx_buf_lock; int /*<<< orphan*/  state; TYPE_2__ ctrl; TYPE_1__ framer; struct device* dev; int /*<<< orphan*/  base; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_TRIGGER_HIGH ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QCOM_SLIM_NGD_CTRL_DOWN ; 
 int SLIM_CL_PER_SUPERFRAME_DIV8 ; 
 int /*<<< orphan*/  SLIM_MAX_CLK_GEAR ; 
 int SLIM_ROOT_FREQ ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct qcom_slim_ngd_ctrl*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct qcom_slim_ngd_ctrl* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct qcom_slim_ngd_ctrl*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int of_qcom_slim_ngd_register (struct device*,struct qcom_slim_ngd_ctrl*) ; 
 int /*<<< orphan*/  platform_driver_register (int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qcom_slim_ngd_driver ; 
 int /*<<< orphan*/  qcom_slim_ngd_enable_stream ; 
 int /*<<< orphan*/  qcom_slim_ngd_get_laddr ; 
 int /*<<< orphan*/  qcom_slim_ngd_interrupt ; 
 int /*<<< orphan*/  qcom_slim_ngd_xfer_msg ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qcom_slim_ngd_ctrl_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct qcom_slim_ngd_ctrl *ctrl;
	struct resource *res;
	int ret;

	ctrl = devm_kzalloc(dev, sizeof(*ctrl), GFP_KERNEL);
	if (!ctrl)
		return -ENOMEM;

	dev_set_drvdata(dev, ctrl);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	ctrl->base = devm_ioremap_resource(dev, res);
	if (IS_ERR(ctrl->base))
		return PTR_ERR(ctrl->base);

	res = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	if (!res) {
		dev_err(&pdev->dev, "no slimbus IRQ resource\n");
		return -ENODEV;
	}

	ret = devm_request_irq(dev, res->start, qcom_slim_ngd_interrupt,
			       IRQF_TRIGGER_HIGH, "slim-ngd", ctrl);
	if (ret) {
		dev_err(&pdev->dev, "request IRQ failed\n");
		return ret;
	}

	ctrl->dev = dev;
	ctrl->framer.rootfreq = SLIM_ROOT_FREQ >> 3;
	ctrl->framer.superfreq =
		ctrl->framer.rootfreq / SLIM_CL_PER_SUPERFRAME_DIV8;

	ctrl->ctrl.a_framer = &ctrl->framer;
	ctrl->ctrl.clkgear = SLIM_MAX_CLK_GEAR;
	ctrl->ctrl.get_laddr = qcom_slim_ngd_get_laddr;
	ctrl->ctrl.enable_stream = qcom_slim_ngd_enable_stream;
	ctrl->ctrl.xfer_msg = qcom_slim_ngd_xfer_msg;
	ctrl->ctrl.wakeup = NULL;
	ctrl->state = QCOM_SLIM_NGD_CTRL_DOWN;

	spin_lock_init(&ctrl->tx_buf_lock);
	init_completion(&ctrl->reconf);
	init_completion(&ctrl->qmi.qmi_comp);

	platform_driver_register(&qcom_slim_ngd_driver);
	return of_qcom_slim_ngd_register(dev, ctrl);
}