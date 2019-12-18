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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  nregs; int /*<<< orphan*/  regs; scalar_t__ base; } ;
struct vc4_hvs {TYPE_1__ regset; int /*<<< orphan*/  mitchell_netravali_filter; int /*<<< orphan*/  lbm_mm; int /*<<< orphan*/  dlist_mm; int /*<<< orphan*/  mm_lock; scalar_t__ regs; scalar_t__ dlist; struct platform_device* pdev; } ;
struct vc4_dev {struct vc4_hvs* hvs; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct drm_device {struct vc4_dev* dev_private; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HVS_BOOTLOADER_DLIST_END ; 
 int HVS_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HVS_WRITE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  SCALER_DISPCTRL ; 
 int SCALER_DISPCTRL_DISPEIRQ (int) ; 
 int SCALER_DISPCTRL_DMAEIRQ ; 
 int /*<<< orphan*/  SCALER_DISPCTRL_DSP3_MUX ; 
 int SCALER_DISPCTRL_DSP3_MUX_MASK ; 
 int SCALER_DISPCTRL_DSPEIEOF (int) ; 
 int SCALER_DISPCTRL_DSPEIEOLN (int) ; 
 int SCALER_DISPCTRL_DSPEISLUR (int) ; 
 int SCALER_DISPCTRL_ENABLE ; 
 int SCALER_DISPCTRL_SCLEIRQ ; 
 int SCALER_DISPCTRL_SLVRDEIRQ ; 
 int SCALER_DISPCTRL_SLVWREIRQ ; 
 int SCALER_DLIST_SIZE ; 
 scalar_t__ SCALER_DLIST_START ; 
 int VC4_SET_FIELD (int,int /*<<< orphan*/ ) ; 
 struct drm_device* dev_get_drvdata (struct device*) ; 
 struct vc4_hvs* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct drm_device*) ; 
 int /*<<< orphan*/  drm_mm_init (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  hvs_regs ; 
 int /*<<< orphan*/  mitchell_netravali_1_3_1_3_kernel ; 
 int /*<<< orphan*/  platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 struct platform_device* to_platform_device (struct device*) ; 
 int /*<<< orphan*/  vc4_debugfs_add_file (struct drm_device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vc4_debugfs_add_regset32 (struct drm_device*,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  vc4_hvs_debugfs_underrun ; 
 int /*<<< orphan*/  vc4_hvs_irq_handler ; 
 int vc4_hvs_upload_linear_kernel (struct vc4_hvs*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ vc4_ioremap_regs (struct platform_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vc4_hvs_bind(struct device *dev, struct device *master, void *data)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct drm_device *drm = dev_get_drvdata(master);
	struct vc4_dev *vc4 = drm->dev_private;
	struct vc4_hvs *hvs = NULL;
	int ret;
	u32 dispctrl;

	hvs = devm_kzalloc(&pdev->dev, sizeof(*hvs), GFP_KERNEL);
	if (!hvs)
		return -ENOMEM;

	hvs->pdev = pdev;

	hvs->regs = vc4_ioremap_regs(pdev, 0);
	if (IS_ERR(hvs->regs))
		return PTR_ERR(hvs->regs);

	hvs->regset.base = hvs->regs;
	hvs->regset.regs = hvs_regs;
	hvs->regset.nregs = ARRAY_SIZE(hvs_regs);

	hvs->dlist = hvs->regs + SCALER_DLIST_START;

	spin_lock_init(&hvs->mm_lock);

	/* Set up the HVS display list memory manager.  We never
	 * overwrite the setup from the bootloader (just 128b out of
	 * our 16K), since we don't want to scramble the screen when
	 * transitioning from the firmware's boot setup to runtime.
	 */
	drm_mm_init(&hvs->dlist_mm,
		    HVS_BOOTLOADER_DLIST_END,
		    (SCALER_DLIST_SIZE >> 2) - HVS_BOOTLOADER_DLIST_END);

	/* Set up the HVS LBM memory manager.  We could have some more
	 * complicated data structure that allowed reuse of LBM areas
	 * between planes when they don't overlap on the screen, but
	 * for now we just allocate globally.
	 */
	drm_mm_init(&hvs->lbm_mm, 0, 96 * 1024);

	/* Upload filter kernels.  We only have the one for now, so we
	 * keep it around for the lifetime of the driver.
	 */
	ret = vc4_hvs_upload_linear_kernel(hvs,
					   &hvs->mitchell_netravali_filter,
					   mitchell_netravali_1_3_1_3_kernel);
	if (ret)
		return ret;

	vc4->hvs = hvs;

	dispctrl = HVS_READ(SCALER_DISPCTRL);

	dispctrl |= SCALER_DISPCTRL_ENABLE;
	dispctrl |= SCALER_DISPCTRL_DISPEIRQ(0) |
		    SCALER_DISPCTRL_DISPEIRQ(1) |
		    SCALER_DISPCTRL_DISPEIRQ(2);

	/* Set DSP3 (PV1) to use HVS channel 2, which would otherwise
	 * be unused.
	 */
	dispctrl &= ~SCALER_DISPCTRL_DSP3_MUX_MASK;
	dispctrl &= ~(SCALER_DISPCTRL_DMAEIRQ |
		      SCALER_DISPCTRL_SLVWREIRQ |
		      SCALER_DISPCTRL_SLVRDEIRQ |
		      SCALER_DISPCTRL_DSPEIEOF(0) |
		      SCALER_DISPCTRL_DSPEIEOF(1) |
		      SCALER_DISPCTRL_DSPEIEOF(2) |
		      SCALER_DISPCTRL_DSPEIEOLN(0) |
		      SCALER_DISPCTRL_DSPEIEOLN(1) |
		      SCALER_DISPCTRL_DSPEIEOLN(2) |
		      SCALER_DISPCTRL_DSPEISLUR(0) |
		      SCALER_DISPCTRL_DSPEISLUR(1) |
		      SCALER_DISPCTRL_DSPEISLUR(2) |
		      SCALER_DISPCTRL_SCLEIRQ);
	dispctrl |= VC4_SET_FIELD(2, SCALER_DISPCTRL_DSP3_MUX);

	HVS_WRITE(SCALER_DISPCTRL, dispctrl);

	ret = devm_request_irq(dev, platform_get_irq(pdev, 0),
			       vc4_hvs_irq_handler, 0, "vc4 hvs", drm);
	if (ret)
		return ret;

	vc4_debugfs_add_regset32(drm, "hvs_regs", &hvs->regset);
	vc4_debugfs_add_file(drm, "hvs_underrun", vc4_hvs_debugfs_underrun,
			     NULL);

	return 0;
}