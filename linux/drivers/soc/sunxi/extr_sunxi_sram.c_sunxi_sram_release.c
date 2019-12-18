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
struct sunxi_sram_desc {int claimed; } ;
struct sunxi_sram_data {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct sunxi_sram_data const*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sram_lock ; 
 struct sunxi_sram_data* sunxi_sram_of_parse (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct sunxi_sram_desc* to_sram_desc (struct sunxi_sram_data const*) ; 

int sunxi_sram_release(struct device *dev)
{
	const struct sunxi_sram_data *sram_data;
	struct sunxi_sram_desc *sram_desc;

	if (!dev || !dev->of_node)
		return -EINVAL;

	sram_data = sunxi_sram_of_parse(dev->of_node, NULL);
	if (IS_ERR(sram_data))
		return -EINVAL;

	sram_desc = to_sram_desc(sram_data);

	spin_lock(&sram_lock);
	sram_desc->claimed = false;
	spin_unlock(&sram_lock);

	return 0;
}