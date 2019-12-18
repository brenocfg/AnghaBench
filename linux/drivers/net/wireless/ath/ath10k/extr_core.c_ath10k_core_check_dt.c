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
struct device_node {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  bdf_ext; } ;
struct ath10k {TYPE_2__ id; TYPE_1__* dev; } ;
struct TYPE_3__ {struct device_node* of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_BOOT ; 
 int ENODATA ; 
 int ENOENT ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  of_property_read_string (struct device_node*,char*,char const**) ; 
 scalar_t__ strscpy (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static int ath10k_core_check_dt(struct ath10k *ar)
{
	struct device_node *node;
	const char *variant = NULL;

	node = ar->dev->of_node;
	if (!node)
		return -ENOENT;

	of_property_read_string(node, "qcom,ath10k-calibration-variant",
				&variant);
	if (!variant)
		return -ENODATA;

	if (strscpy(ar->id.bdf_ext, variant, sizeof(ar->id.bdf_ext)) < 0)
		ath10k_dbg(ar, ATH10K_DBG_BOOT,
			   "bdf variant string is longer than the buffer can accommodate (variant: %s)\n",
			    variant);

	return 0;
}