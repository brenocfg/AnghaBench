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
struct xgene_phy_ctx {scalar_t__ mode; struct phy* phy; } ;
struct phy {int dummy; } ;
struct of_phandle_args {scalar_t__ args_count; scalar_t__* args; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct phy* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ MODE_MAX ; 
 scalar_t__ MODE_SATA ; 
 struct xgene_phy_ctx* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static struct phy *xgene_phy_xlate(struct device *dev,
				   struct of_phandle_args *args)
{
	struct xgene_phy_ctx *ctx = dev_get_drvdata(dev);

	if (args->args_count <= 0)
		return ERR_PTR(-EINVAL);
	if (args->args[0] < MODE_SATA || args->args[0] >= MODE_MAX)
		return ERR_PTR(-EINVAL);

	ctx->mode = args->args[0];
	return ctx->phy;
}