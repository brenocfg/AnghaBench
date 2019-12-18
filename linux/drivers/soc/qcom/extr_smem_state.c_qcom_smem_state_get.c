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
struct qcom_smem_state {int dummy; } ;
struct of_phandle_args {int args_count; unsigned int* args; int /*<<< orphan*/  np; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 struct qcom_smem_state* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct qcom_smem_state*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 
 struct qcom_smem_state* of_node_to_state (int /*<<< orphan*/ ) ; 
 int of_parse_phandle_with_args (int /*<<< orphan*/ ,char*,char*,int,struct of_phandle_args*) ; 
 int of_property_match_string (int /*<<< orphan*/ ,char*,char const*) ; 

struct qcom_smem_state *qcom_smem_state_get(struct device *dev,
					    const char *con_id,
					    unsigned *bit)
{
	struct qcom_smem_state *state;
	struct of_phandle_args args;
	int index = 0;
	int ret;

	if (con_id) {
		index = of_property_match_string(dev->of_node,
						 "qcom,smem-state-names",
						 con_id);
		if (index < 0) {
			dev_err(dev, "missing qcom,smem-state-names\n");
			return ERR_PTR(index);
		}
	}

	ret = of_parse_phandle_with_args(dev->of_node,
					 "qcom,smem-states",
					 "#qcom,smem-state-cells",
					 index,
					 &args);
	if (ret) {
		dev_err(dev, "failed to parse qcom,smem-states property\n");
		return ERR_PTR(ret);
	}

	if (args.args_count != 1) {
		dev_err(dev, "invalid #qcom,smem-state-cells\n");
		return ERR_PTR(-EINVAL);
	}

	state = of_node_to_state(args.np);
	if (IS_ERR(state))
		goto put;

	*bit = args.args[0];

put:
	of_node_put(args.np);
	return state;
}