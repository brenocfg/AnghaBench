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
struct sunxi_glue {int /*<<< orphan*/  flags; int /*<<< orphan*/  clk; int /*<<< orphan*/  rst; int /*<<< orphan*/  phy; int /*<<< orphan*/  host_nb; int /*<<< orphan*/  extcon; int /*<<< orphan*/  dev; int /*<<< orphan*/  xceiv; } ;
struct musb {TYPE_1__* controller; int /*<<< orphan*/  isr; scalar_t__ mregs; int /*<<< orphan*/  xceiv; int /*<<< orphan*/  phy; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXTCON_USB_HOST ; 
 int /*<<< orphan*/  SUNXI_MUSB_FL_HAS_RESET ; 
 int /*<<< orphan*/  SUNXI_MUSB_FL_HAS_SRAM ; 
 scalar_t__ SUNXI_MUSB_VEND0 ; 
 int /*<<< orphan*/  SUNXI_MUSB_VEND0_PIO_MODE ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 struct sunxi_glue* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int devm_extcon_register_notifier (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int phy_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get (TYPE_1__*) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int reset_control_deassert (int /*<<< orphan*/ ) ; 
 struct musb* sunxi_musb ; 
 int /*<<< orphan*/  sunxi_musb_interrupt ; 
 int sunxi_sram_claim (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sunxi_sram_release (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int sunxi_musb_init(struct musb *musb)
{
	struct sunxi_glue *glue = dev_get_drvdata(musb->controller->parent);
	int ret;

	sunxi_musb = musb;
	musb->phy = glue->phy;
	musb->xceiv = glue->xceiv;

	if (test_bit(SUNXI_MUSB_FL_HAS_SRAM, &glue->flags)) {
		ret = sunxi_sram_claim(musb->controller->parent);
		if (ret)
			return ret;
	}

	ret = clk_prepare_enable(glue->clk);
	if (ret)
		goto error_sram_release;

	if (test_bit(SUNXI_MUSB_FL_HAS_RESET, &glue->flags)) {
		ret = reset_control_deassert(glue->rst);
		if (ret)
			goto error_clk_disable;
	}

	writeb(SUNXI_MUSB_VEND0_PIO_MODE, musb->mregs + SUNXI_MUSB_VEND0);

	/* Register notifier before calling phy_init() */
	ret = devm_extcon_register_notifier(glue->dev, glue->extcon,
					EXTCON_USB_HOST, &glue->host_nb);
	if (ret)
		goto error_reset_assert;

	ret = phy_init(glue->phy);
	if (ret)
		goto error_reset_assert;

	musb->isr = sunxi_musb_interrupt;

	/* Stop the musb-core from doing runtime pm (not supported on sunxi) */
	pm_runtime_get(musb->controller);

	return 0;

error_reset_assert:
	if (test_bit(SUNXI_MUSB_FL_HAS_RESET, &glue->flags))
		reset_control_assert(glue->rst);
error_clk_disable:
	clk_disable_unprepare(glue->clk);
error_sram_release:
	if (test_bit(SUNXI_MUSB_FL_HAS_SRAM, &glue->flags))
		sunxi_sram_release(musb->controller->parent);
	return ret;
}