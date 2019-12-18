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
struct tegra_dsi_state {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  state; } ;
struct TYPE_4__ {TYPE_1__ connector; } ;
struct tegra_dsi {TYPE_2__ output; } ;

/* Variables and functions */
 struct tegra_dsi_state* to_dsi_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct tegra_dsi_state *tegra_dsi_get_state(struct tegra_dsi *dsi)
{
	return to_dsi_state(dsi->output.connector.state);
}