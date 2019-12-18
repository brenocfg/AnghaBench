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
typedef  int /*<<< orphan*/  u32 ;
struct reset_controller_dev {int dummy; } ;
struct lantiq_rcu_reset_priv {int /*<<< orphan*/  dev; int /*<<< orphan*/  reset_offset; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int lantiq_rcu_reset_status_timeout (struct reset_controller_dev*,unsigned long,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct lantiq_rcu_reset_priv* to_lantiq_rcu_reset_priv (struct reset_controller_dev*) ; 

__attribute__((used)) static int lantiq_rcu_reset_update(struct reset_controller_dev *rcdev,
				   unsigned long id, bool assert)
{
	struct lantiq_rcu_reset_priv *priv = to_lantiq_rcu_reset_priv(rcdev);
	unsigned int set = id & 0x1f;
	u32 val = assert ? BIT(set) : 0;
	int ret;

	ret = regmap_update_bits(priv->regmap, priv->reset_offset, BIT(set),
				 val);
	if (ret) {
		dev_err(priv->dev, "Failed to set reset bit %u\n", set);
		return ret;
	}


	ret = lantiq_rcu_reset_status_timeout(rcdev, id, assert);
	if (ret)
		dev_err(priv->dev, "Failed to %s bit %u\n",
			assert ? "assert" : "deassert", set);

	return ret;
}