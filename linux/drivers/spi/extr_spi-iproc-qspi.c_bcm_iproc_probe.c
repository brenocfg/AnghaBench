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
struct resource {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct bcm_qspi_soc_intc {int /*<<< orphan*/  bcm_qspi_get_int_status; int /*<<< orphan*/  (* bcm_qspi_int_set ) (struct bcm_qspi_soc_intc*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* bcm_qspi_int_ack ) (struct bcm_qspi_soc_intc*,int /*<<< orphan*/ ) ;} ;
struct bcm_iproc_intc {int /*<<< orphan*/  big_endian; void* int_status_reg; void* int_reg; int /*<<< orphan*/  soclock; struct platform_device* pdev; struct bcm_qspi_soc_intc soc_intc; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  MSPI_BSPI_DONE ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  bcm_iproc_qspi_get_l2_int_status ; 
 int /*<<< orphan*/  bcm_iproc_qspi_int_ack (struct bcm_qspi_soc_intc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm_iproc_qspi_int_set (struct bcm_qspi_soc_intc*,int /*<<< orphan*/ ,int) ; 
 int bcm_qspi_probe (struct platform_device*,struct bcm_qspi_soc_intc*) ; 
 void* devm_ioremap_resource (struct device*,struct resource*) ; 
 struct bcm_iproc_intc* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_device_is_big_endian (int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bcm_iproc_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct bcm_iproc_intc *priv;
	struct bcm_qspi_soc_intc *soc_intc;
	struct resource *res;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;
	soc_intc = &priv->soc_intc;
	priv->pdev = pdev;

	spin_lock_init(&priv->soclock);

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "intr_regs");
	priv->int_reg = devm_ioremap_resource(dev, res);
	if (IS_ERR(priv->int_reg))
		return PTR_ERR(priv->int_reg);

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM,
					   "intr_status_reg");
	priv->int_status_reg = devm_ioremap_resource(dev, res);
	if (IS_ERR(priv->int_status_reg))
		return PTR_ERR(priv->int_status_reg);

	priv->big_endian = of_device_is_big_endian(dev->of_node);

	bcm_iproc_qspi_int_ack(soc_intc, MSPI_BSPI_DONE);
	bcm_iproc_qspi_int_set(soc_intc, MSPI_BSPI_DONE, false);

	soc_intc->bcm_qspi_int_ack = bcm_iproc_qspi_int_ack;
	soc_intc->bcm_qspi_int_set = bcm_iproc_qspi_int_set;
	soc_intc->bcm_qspi_get_int_status = bcm_iproc_qspi_get_l2_int_status;

	return bcm_qspi_probe(pdev, soc_intc);
}