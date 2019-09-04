#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct tegra_dc {int pipe; TYPE_2__* dev; TYPE_1__* soc; } ;
struct device_link {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  driver; } ;
struct TYPE_5__ {scalar_t__ coupled_pm; } ;

/* Variables and functions */
 int DL_FLAG_AUTOREMOVE_CONSUMER ; 
 int DL_FLAG_PM_RUNTIME ; 
 int EINVAL ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  dev_dbg (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 struct device_link* device_link_add (TYPE_2__*,struct device*,int) ; 
 struct device* driver_find_device (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_dc_match_by_pipe ; 

__attribute__((used)) static int tegra_dc_couple(struct tegra_dc *dc)
{
	/*
	 * On Tegra20, DC1 requires DC0 to be taken out of reset in order to
	 * be enabled, otherwise CPU hangs on writing to CMD_DISPLAY_COMMAND /
	 * POWER_CONTROL registers during CRTC enabling.
	 */
	if (dc->soc->coupled_pm && dc->pipe == 1) {
		u32 flags = DL_FLAG_PM_RUNTIME | DL_FLAG_AUTOREMOVE_CONSUMER;
		struct device_link *link;
		struct device *partner;

		partner = driver_find_device(dc->dev->driver, NULL, NULL,
					     tegra_dc_match_by_pipe);
		if (!partner)
			return -EPROBE_DEFER;

		link = device_link_add(dc->dev, partner, flags);
		if (!link) {
			dev_err(dc->dev, "failed to link controllers\n");
			return -EINVAL;
		}

		dev_dbg(dc->dev, "coupled to %s\n", dev_name(partner));
	}

	return 0;
}