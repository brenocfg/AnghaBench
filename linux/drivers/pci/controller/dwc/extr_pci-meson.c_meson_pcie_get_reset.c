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
typedef  scalar_t__ u32 ;
struct reset_control {int dummy; } ;
struct TYPE_2__ {struct device* dev; } ;
struct meson_pcie {TYPE_1__ pci; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ PCIE_SHARED_RESET ; 
 struct reset_control* devm_reset_control_get (struct device*,char const*) ; 
 struct reset_control* devm_reset_control_get_shared (struct device*,char const*) ; 

__attribute__((used)) static struct reset_control *meson_pcie_get_reset(struct meson_pcie *mp,
						  const char *id,
						  u32 reset_type)
{
	struct device *dev = mp->pci.dev;
	struct reset_control *reset;

	if (reset_type == PCIE_SHARED_RESET)
		reset = devm_reset_control_get_shared(dev, id);
	else
		reset = devm_reset_control_get(dev, id);

	return reset;
}