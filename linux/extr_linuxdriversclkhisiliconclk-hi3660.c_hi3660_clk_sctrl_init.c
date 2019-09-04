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
struct hisi_clock_data {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hi3660_sctrl_divider_clks ; 
 int /*<<< orphan*/  hi3660_sctrl_gate_clks ; 
 int /*<<< orphan*/  hi3660_sctrl_gate_sep_clks ; 
 int /*<<< orphan*/  hi3660_sctrl_mux_clks ; 
 struct hisi_clock_data* hisi_clk_init (struct device_node*,int) ; 
 int /*<<< orphan*/  hisi_clk_register_divider (int /*<<< orphan*/ ,int,struct hisi_clock_data*) ; 
 int /*<<< orphan*/  hisi_clk_register_gate (int /*<<< orphan*/ ,int,struct hisi_clock_data*) ; 
 int /*<<< orphan*/  hisi_clk_register_gate_sep (int /*<<< orphan*/ ,int,struct hisi_clock_data*) ; 
 int /*<<< orphan*/  hisi_clk_register_mux (int /*<<< orphan*/ ,int,struct hisi_clock_data*) ; 

__attribute__((used)) static void hi3660_clk_sctrl_init(struct device_node *np)
{
	struct hisi_clock_data *clk_data;
	int nr = ARRAY_SIZE(hi3660_sctrl_gate_clks) +
		 ARRAY_SIZE(hi3660_sctrl_gate_sep_clks) +
		 ARRAY_SIZE(hi3660_sctrl_mux_clks) +
		 ARRAY_SIZE(hi3660_sctrl_divider_clks);

	clk_data = hisi_clk_init(np, nr);
	if (!clk_data)
		return;
	hisi_clk_register_gate(hi3660_sctrl_gate_clks,
			       ARRAY_SIZE(hi3660_sctrl_gate_clks), clk_data);
	hisi_clk_register_gate_sep(hi3660_sctrl_gate_sep_clks,
				   ARRAY_SIZE(hi3660_sctrl_gate_sep_clks),
				   clk_data);
	hisi_clk_register_mux(hi3660_sctrl_mux_clks,
			      ARRAY_SIZE(hi3660_sctrl_mux_clks), clk_data);
	hisi_clk_register_divider(hi3660_sctrl_divider_clks,
				  ARRAY_SIZE(hi3660_sctrl_divider_clks),
				  clk_data);
}