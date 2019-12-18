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
struct TYPE_3__ {int /*<<< orphan*/  nregs; int /*<<< orphan*/  regs; int /*<<< orphan*/  base; } ;
struct TYPE_4__ {int /*<<< orphan*/  base; } ;
struct vc4_txp {TYPE_1__ regset; TYPE_2__ connector; int /*<<< orphan*/  regs; struct platform_device* pdev; } ;
struct vc4_dev {struct vc4_txp* txp; } ;
struct platform_device {int dummy; } ;
struct drm_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 struct drm_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct vc4_txp*) ; 
 struct vc4_txp* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vc4_txp*) ; 
 int /*<<< orphan*/  drm_connector_helper_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_fmts ; 
 int drm_writeback_connector_init (struct drm_device*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct platform_device* to_platform_device (struct device*) ; 
 struct vc4_dev* to_vc4_dev (struct drm_device*) ; 
 int /*<<< orphan*/  txp_regs ; 
 int /*<<< orphan*/  vc4_debugfs_add_regset32 (struct drm_device*,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  vc4_ioremap_regs (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc4_txp_connector_funcs ; 
 int /*<<< orphan*/  vc4_txp_connector_helper_funcs ; 
 int /*<<< orphan*/  vc4_txp_encoder_helper_funcs ; 
 int /*<<< orphan*/  vc4_txp_interrupt ; 

__attribute__((used)) static int vc4_txp_bind(struct device *dev, struct device *master, void *data)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct drm_device *drm = dev_get_drvdata(master);
	struct vc4_dev *vc4 = to_vc4_dev(drm);
	struct vc4_txp *txp;
	int ret, irq;

	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return irq;

	txp = devm_kzalloc(dev, sizeof(*txp), GFP_KERNEL);
	if (!txp)
		return -ENOMEM;

	txp->pdev = pdev;

	txp->regs = vc4_ioremap_regs(pdev, 0);
	if (IS_ERR(txp->regs))
		return PTR_ERR(txp->regs);
	txp->regset.base = txp->regs;
	txp->regset.regs = txp_regs;
	txp->regset.nregs = ARRAY_SIZE(txp_regs);

	drm_connector_helper_add(&txp->connector.base,
				 &vc4_txp_connector_helper_funcs);
	ret = drm_writeback_connector_init(drm, &txp->connector,
					   &vc4_txp_connector_funcs,
					   &vc4_txp_encoder_helper_funcs,
					   drm_fmts, ARRAY_SIZE(drm_fmts));
	if (ret)
		return ret;

	ret = devm_request_irq(dev, irq, vc4_txp_interrupt, 0,
			       dev_name(dev), txp);
	if (ret)
		return ret;

	dev_set_drvdata(dev, txp);
	vc4->txp = txp;

	vc4_debugfs_add_regset32(drm, "txp_regs", &txp->regset);

	return 0;
}