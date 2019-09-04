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
struct slimpro_i2c_dev {int /*<<< orphan*/  mbox_chan; int /*<<< orphan*/  adapter; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ acpi_disabled ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbox_free_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcc_mbox_free_channel (int /*<<< orphan*/ ) ; 
 struct slimpro_i2c_dev* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int xgene_slimpro_i2c_remove(struct platform_device *pdev)
{
	struct slimpro_i2c_dev *ctx = platform_get_drvdata(pdev);

	i2c_del_adapter(&ctx->adapter);

	if (acpi_disabled)
		mbox_free_channel(ctx->mbox_chan);
	else
		pcc_mbox_free_channel(ctx->mbox_chan);

	return 0;
}