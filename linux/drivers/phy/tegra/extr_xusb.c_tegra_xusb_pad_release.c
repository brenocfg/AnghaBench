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
struct tegra_xusb_pad {TYPE_2__* soc; } ;
struct device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* remove ) (struct tegra_xusb_pad*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct tegra_xusb_pad*) ; 
 struct tegra_xusb_pad* to_tegra_xusb_pad (struct device*) ; 

__attribute__((used)) static void tegra_xusb_pad_release(struct device *dev)
{
	struct tegra_xusb_pad *pad = to_tegra_xusb_pad(dev);

	pad->soc->ops->remove(pad);
}