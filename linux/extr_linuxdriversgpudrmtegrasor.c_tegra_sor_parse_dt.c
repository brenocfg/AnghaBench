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
typedef  scalar_t__ u32 ;
struct tegra_sor {scalar_t__ index; scalar_t__ pad; TYPE_2__* soc; TYPE_1__* dev; } ;
struct device_node {int dummy; } ;
struct TYPE_4__ {scalar_t__ has_nvdisplay; } ;
struct TYPE_3__ {struct device_node* of_node; } ;

/* Variables and functions */
 scalar_t__ TEGRA_IO_PAD_HDMI_DP0 ; 
 int of_property_read_u32 (struct device_node*,char*,scalar_t__*) ; 

__attribute__((used)) static int tegra_sor_parse_dt(struct tegra_sor *sor)
{
	struct device_node *np = sor->dev->of_node;
	u32 value;
	int err;

	if (sor->soc->has_nvdisplay) {
		err = of_property_read_u32(np, "nvidia,interface", &value);
		if (err < 0)
			return err;

		sor->index = value;

		/*
		 * override the default that we already set for Tegra210 and
		 * earlier
		 */
		sor->pad = TEGRA_IO_PAD_HDMI_DP0 + sor->index;
	}

	return 0;
}