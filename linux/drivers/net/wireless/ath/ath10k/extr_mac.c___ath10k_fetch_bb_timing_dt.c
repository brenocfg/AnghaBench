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
struct wmi_bb_timing_cfg_arg {int bb_tx_timing; int bb_xpa_timing; } ;
struct device_node {int dummy; } ;
struct ath10k {TYPE_1__* dev; } ;
struct TYPE_2__ {struct device_node* of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_BOOT ; 
 int ENOENT ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int,int) ; 
 int of_property_read_string_index (struct device_node*,char*,int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  strcmp (char*,char const*) ; 

__attribute__((used)) static int __ath10k_fetch_bb_timing_dt(struct ath10k *ar,
				       struct wmi_bb_timing_cfg_arg *bb_timing)
{
	struct device_node *node;
	const char *fem_name;
	int ret;

	node = ar->dev->of_node;
	if (!node)
		return -ENOENT;

	ret = of_property_read_string_index(node, "ext-fem-name", 0, &fem_name);
	if (ret)
		return -ENOENT;

	/*
	 * If external Front End module used in hardware, then default base band timing
	 * parameter cannot be used since they were fine tuned for reference hardware,
	 * so choosing different value suitable for that external FEM.
	 */
	if (!strcmp("microsemi-lx5586", fem_name)) {
		bb_timing->bb_tx_timing = 0x00;
		bb_timing->bb_xpa_timing = 0x0101;
	} else {
		return -ENOENT;
	}

	ath10k_dbg(ar, ATH10K_DBG_BOOT, "boot bb_tx_timing 0x%x bb_xpa_timing 0x%x\n",
		   bb_timing->bb_tx_timing, bb_timing->bb_xpa_timing);
	return 0;
}