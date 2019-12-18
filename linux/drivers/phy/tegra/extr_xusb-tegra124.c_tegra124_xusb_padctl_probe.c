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
struct tegra_xusb_padctl_soc {int dummy; } ;
struct tegra_xusb_padctl {struct tegra_xusb_padctl_soc const* soc; struct device* dev; } ;
struct tegra124_xusb_padctl {struct tegra_xusb_padctl base; int /*<<< orphan*/  fuse; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct tegra_xusb_padctl* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct tegra124_xusb_padctl* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int tegra124_xusb_read_fuse_calibration (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct tegra_xusb_padctl *
tegra124_xusb_padctl_probe(struct device *dev,
			   const struct tegra_xusb_padctl_soc *soc)
{
	struct tegra124_xusb_padctl *padctl;
	int err;

	padctl = devm_kzalloc(dev, sizeof(*padctl), GFP_KERNEL);
	if (!padctl)
		return ERR_PTR(-ENOMEM);

	padctl->base.dev = dev;
	padctl->base.soc = soc;

	err = tegra124_xusb_read_fuse_calibration(&padctl->fuse);
	if (err < 0)
		return ERR_PTR(err);

	return &padctl->base;
}