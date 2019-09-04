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
union ib_flow_spec {int type; int size; } ;
struct mlx4_ib_dev {int /*<<< orphan*/  dev; } ;
struct ib_qp {int dummy; } ;
struct ib_flow_spec_ib {int dummy; } ;
struct default_rules {int* rules_create_list; } ;
struct _rule_hw {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int EINVAL ; 
#define  IB_FLOW_SPEC_IB 128 
 int parse_flow_attr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union ib_flow_spec*,struct _rule_hw*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static int __mlx4_ib_create_default_rules(
		struct mlx4_ib_dev *mdev,
		struct ib_qp *qp,
		const struct default_rules *pdefault_rules,
		struct _rule_hw *mlx4_spec) {
	int size = 0;
	int i;

	for (i = 0; i < ARRAY_SIZE(pdefault_rules->rules_create_list); i++) {
		int ret;
		union ib_flow_spec ib_spec;
		switch (pdefault_rules->rules_create_list[i]) {
		case 0:
			/* no rule */
			continue;
		case IB_FLOW_SPEC_IB:
			ib_spec.type = IB_FLOW_SPEC_IB;
			ib_spec.size = sizeof(struct ib_flow_spec_ib);

			break;
		default:
			/* invalid rule */
			return -EINVAL;
		}
		/* We must put empty rule, qpn is being ignored */
		ret = parse_flow_attr(mdev->dev, 0, &ib_spec,
				      mlx4_spec);
		if (ret < 0) {
			pr_info("invalid parsing\n");
			return -EINVAL;
		}

		mlx4_spec = (void *)mlx4_spec + ret;
		size += ret;
	}
	return size;
}