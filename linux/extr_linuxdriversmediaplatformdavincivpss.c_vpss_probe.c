#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct TYPE_9__ {char* platform_data; } ;
struct platform_device {TYPE_2__ dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  clear_wbl_overflow; int /*<<< orphan*/  select_ccdc_source; int /*<<< orphan*/  enable_clock; } ;
struct TYPE_10__ {scalar_t__ platform; int /*<<< orphan*/  vpss_lock; TYPE_1__ hw_ops; void* vpss_regs_base1; void* vpss_regs_base0; } ;

/* Variables and functions */
 scalar_t__ DM355 ; 
 int /*<<< orphan*/  DM355_VPSSBL_EVTSEL ; 
 int /*<<< orphan*/  DM355_VPSSBL_EVTSEL_DEFAULT ; 
 int /*<<< orphan*/  DM355_VPSSBL_INTSEL ; 
 int /*<<< orphan*/  DM355_VPSSBL_INTSEL_DEFAULT ; 
 scalar_t__ DM365 ; 
 int /*<<< orphan*/  DM365_ISP5_BCR ; 
 int DM365_ISP5_BCR_ISIF_OUT_ENABLE ; 
 int /*<<< orphan*/  DM365_ISP5_INTSEL1 ; 
 int DM365_ISP5_INTSEL1_DEFAULT ; 
 int /*<<< orphan*/  DM365_ISP5_INTSEL2 ; 
 int DM365_ISP5_INTSEL2_DEFAULT ; 
 int /*<<< orphan*/  DM365_ISP5_INTSEL3 ; 
 int DM365_ISP5_INTSEL3_DEFAULT ; 
 int /*<<< orphan*/  DM365_ISP5_PCCR ; 
 int DM365_ISP5_PCCR_BL_CLK_ENABLE ; 
 int DM365_ISP5_PCCR_H3A_CLK_ENABLE ; 
 int DM365_ISP5_PCCR_IPIPEIF_CLK_ENABLE ; 
 int DM365_ISP5_PCCR_IPIPE_CLK_ENABLE ; 
 int DM365_ISP5_PCCR_ISIF_CLK_ENABLE ; 
 int DM365_ISP5_PCCR_RSV ; 
 int DM365_ISP5_PCCR_RSZ_CLK_ENABLE ; 
 scalar_t__ DM644X ; 
 int ENODEV ; 
 int ENOENT ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  bl_regw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_2__*,char*,char*) ; 
 void* devm_ioremap_resource (TYPE_2__*,struct resource*) ; 
 int /*<<< orphan*/  dm355_enable_clock ; 
 int /*<<< orphan*/  dm355_select_ccdc_source ; 
 int /*<<< orphan*/  dm365_enable_clock ; 
 int /*<<< orphan*/  dm365_select_ccdc_source ; 
 int /*<<< orphan*/  dm644x_clear_wbl_overflow ; 
 int isp5_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp5_write (int,int /*<<< orphan*/ ) ; 
 TYPE_4__ oper_cfg ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_get (TYPE_2__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static int vpss_probe(struct platform_device *pdev)
{
	struct resource *res;
	char *platform_name;

	if (!pdev->dev.platform_data) {
		dev_err(&pdev->dev, "no platform data\n");
		return -ENOENT;
	}

	platform_name = pdev->dev.platform_data;
	if (!strcmp(platform_name, "dm355_vpss"))
		oper_cfg.platform = DM355;
	else if (!strcmp(platform_name, "dm365_vpss"))
		oper_cfg.platform = DM365;
	else if (!strcmp(platform_name, "dm644x_vpss"))
		oper_cfg.platform = DM644X;
	else {
		dev_err(&pdev->dev, "vpss driver not supported on this platform\n");
		return -ENODEV;
	}

	dev_info(&pdev->dev, "%s vpss probed\n", platform_name);
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);

	oper_cfg.vpss_regs_base0 = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(oper_cfg.vpss_regs_base0))
		return PTR_ERR(oper_cfg.vpss_regs_base0);

	if (oper_cfg.platform == DM355 || oper_cfg.platform == DM365) {
		res = platform_get_resource(pdev, IORESOURCE_MEM, 1);

		oper_cfg.vpss_regs_base1 = devm_ioremap_resource(&pdev->dev,
								 res);
		if (IS_ERR(oper_cfg.vpss_regs_base1))
			return PTR_ERR(oper_cfg.vpss_regs_base1);
	}

	if (oper_cfg.platform == DM355) {
		oper_cfg.hw_ops.enable_clock = dm355_enable_clock;
		oper_cfg.hw_ops.select_ccdc_source = dm355_select_ccdc_source;
		/* Setup vpss interrupts */
		bl_regw(DM355_VPSSBL_INTSEL_DEFAULT, DM355_VPSSBL_INTSEL);
		bl_regw(DM355_VPSSBL_EVTSEL_DEFAULT, DM355_VPSSBL_EVTSEL);
	} else if (oper_cfg.platform == DM365) {
		oper_cfg.hw_ops.enable_clock = dm365_enable_clock;
		oper_cfg.hw_ops.select_ccdc_source = dm365_select_ccdc_source;
		/* Setup vpss interrupts */
		isp5_write((isp5_read(DM365_ISP5_PCCR) |
				      DM365_ISP5_PCCR_BL_CLK_ENABLE |
				      DM365_ISP5_PCCR_ISIF_CLK_ENABLE |
				      DM365_ISP5_PCCR_H3A_CLK_ENABLE |
				      DM365_ISP5_PCCR_RSZ_CLK_ENABLE |
				      DM365_ISP5_PCCR_IPIPE_CLK_ENABLE |
				      DM365_ISP5_PCCR_IPIPEIF_CLK_ENABLE |
				      DM365_ISP5_PCCR_RSV), DM365_ISP5_PCCR);
		isp5_write((isp5_read(DM365_ISP5_BCR) |
			    DM365_ISP5_BCR_ISIF_OUT_ENABLE), DM365_ISP5_BCR);
		isp5_write(DM365_ISP5_INTSEL1_DEFAULT, DM365_ISP5_INTSEL1);
		isp5_write(DM365_ISP5_INTSEL2_DEFAULT, DM365_ISP5_INTSEL2);
		isp5_write(DM365_ISP5_INTSEL3_DEFAULT, DM365_ISP5_INTSEL3);
	} else
		oper_cfg.hw_ops.clear_wbl_overflow = dm644x_clear_wbl_overflow;

	pm_runtime_enable(&pdev->dev);

	pm_runtime_get(&pdev->dev);

	spin_lock_init(&oper_cfg.vpss_lock);
	dev_info(&pdev->dev, "%s vpss probe success\n", platform_name);

	return 0;
}