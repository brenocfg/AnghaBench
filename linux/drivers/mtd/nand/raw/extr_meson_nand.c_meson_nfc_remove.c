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
struct platform_device {int dummy; } ;
struct meson_nfc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  meson_nfc_disable_clk (struct meson_nfc*) ; 
 int meson_nfc_nand_chip_cleanup (struct meson_nfc*) ; 
 struct meson_nfc* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int meson_nfc_remove(struct platform_device *pdev)
{
	struct meson_nfc *nfc = platform_get_drvdata(pdev);
	int ret;

	ret = meson_nfc_nand_chip_cleanup(nfc);
	if (ret)
		return ret;

	meson_nfc_disable_clk(nfc);

	platform_set_drvdata(pdev, NULL);

	return 0;
}