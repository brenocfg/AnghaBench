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
struct mlx5_fpga_ipsec_rule {int dummy; } ;
struct mlx5_fpga_ipsec {int /*<<< orphan*/  rules_rb_lock; int /*<<< orphan*/  rules_rb; } ;
struct fs_fte {int dummy; } ;

/* Variables and functions */
 struct mlx5_fpga_ipsec_rule* _rule_search (int /*<<< orphan*/ *,struct fs_fte*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct mlx5_fpga_ipsec_rule *
rule_search(struct mlx5_fpga_ipsec *ipsec_dev, struct fs_fte *fte)
{
	struct mlx5_fpga_ipsec_rule *rule;

	mutex_lock(&ipsec_dev->rules_rb_lock);
	rule = _rule_search(&ipsec_dev->rules_rb, fte);
	mutex_unlock(&ipsec_dev->rules_rb_lock);

	return rule;
}