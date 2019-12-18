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
typedef  int u32 ;
struct reset_controller_dev {int dummy; } ;
struct lantiq_rcu_reset_priv {int /*<<< orphan*/  status_offset; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 struct lantiq_rcu_reset_priv* to_lantiq_rcu_reset_priv (struct reset_controller_dev*) ; 

__attribute__((used)) static int lantiq_rcu_reset_status(struct reset_controller_dev *rcdev,
				   unsigned long id)
{
	struct lantiq_rcu_reset_priv *priv = to_lantiq_rcu_reset_priv(rcdev);
	unsigned int status = (id >> 8) & 0x1f;
	u32 val;
	int ret;

	ret = regmap_read(priv->regmap, priv->status_offset, &val);
	if (ret)
		return ret;

	return !!(val & BIT(status));
}