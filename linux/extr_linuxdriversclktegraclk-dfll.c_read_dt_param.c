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
typedef  int /*<<< orphan*/  u32 ;
struct tegra_dfll {TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,char const*,int) ; 
 int of_property_read_u32 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool read_dt_param(struct tegra_dfll *td, const char *param, u32 *dest)
{
	int err = of_property_read_u32(td->dev->of_node, param, dest);

	if (err < 0) {
		dev_err(td->dev, "failed to read DT parameter %s: %d\n",
			param, err);
		return false;
	}

	return true;
}