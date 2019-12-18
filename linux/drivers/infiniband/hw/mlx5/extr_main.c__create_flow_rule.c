#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
union ib_flow_spec {int /*<<< orphan*/  size; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  u32 ;
struct mlx5_ib_mcounters {int /*<<< orphan*/  hw_cntrs_hndl; } ;
struct mlx5_ib_flow_prio {struct mlx5_flow_table* flow_table; int /*<<< orphan*/  refcount; } ;
struct mlx5_ib_flow_handler {TYPE_3__* ibcounters; struct mlx5_ib_dev* dev; struct mlx5_ib_flow_prio* prio; int /*<<< orphan*/  rule; int /*<<< orphan*/  list; } ;
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; TYPE_1__* port; scalar_t__ is_rep; } ;
struct mlx5_ib_create_flow {int dummy; } ;
struct mlx5_flow_table {int dummy; } ;
struct TYPE_7__ {int flags; int /*<<< orphan*/  flow_tag; } ;
struct mlx5_flow_spec {TYPE_2__ flow_context; int /*<<< orphan*/  match_criteria; int /*<<< orphan*/  match_criteria_enable; } ;
struct mlx5_flow_destination {int /*<<< orphan*/  counter_id; int /*<<< orphan*/  type; } ;
struct mlx5_flow_act {int action; TYPE_3__* counters; } ;
struct mlx5_eswitch_rep {int dummy; } ;
struct ib_flow_attr {int flags; unsigned int num_of_specs; int port; int /*<<< orphan*/  type; } ;
struct TYPE_8__ {int /*<<< orphan*/  usecnt; } ;
struct TYPE_6__ {struct mlx5_eswitch_rep* rep; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct mlx5_ib_flow_handler* ERR_PTR (int) ; 
 int FLOW_CONTEXT_HAS_TAG ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IB_FLOW_ATTR_ALL_DEFAULT ; 
 int IB_FLOW_ATTR_FLAGS_EGRESS ; 
 int /*<<< orphan*/  IB_FLOW_ATTR_MC_DEFAULT ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int MLX5_FLOW_CONTEXT_ACTION_ALLOW ; 
 int MLX5_FLOW_CONTEXT_ACTION_COUNT ; 
 int MLX5_FLOW_CONTEXT_ACTION_DROP ; 
 int MLX5_FLOW_CONTEXT_ACTION_FWD_DEST ; 
 int MLX5_FLOW_CONTEXT_ACTION_FWD_NEXT_PRIO ; 
 int /*<<< orphan*/  MLX5_FLOW_DESTINATION_TYPE_COUNTER ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  counters_clear_description (TYPE_3__*) ; 
 int flow_counters_set_data (TYPE_3__*,struct mlx5_ib_create_flow*) ; 
 int /*<<< orphan*/  flow_is_multicast_only (struct ib_flow_attr const*) ; 
 int /*<<< orphan*/  get_match_criteria_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_valid_attr (int /*<<< orphan*/ ,struct ib_flow_attr const*) ; 
 int /*<<< orphan*/  is_valid_spec (int /*<<< orphan*/ ,struct mlx5_flow_spec*,struct mlx5_flow_act*,int) ; 
 int /*<<< orphan*/  kfree (struct mlx5_ib_flow_handler*) ; 
 int /*<<< orphan*/  kvfree (struct mlx5_flow_spec*) ; 
 struct mlx5_flow_spec* kvzalloc (int,int /*<<< orphan*/ ) ; 
 struct mlx5_ib_flow_handler* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct mlx5_flow_destination*,struct mlx5_flow_destination*,int) ; 
 int /*<<< orphan*/  mlx5_add_flow_rules (struct mlx5_flow_table*,struct mlx5_flow_spec*,struct mlx5_flow_act*,struct mlx5_flow_destination*,int) ; 
 int /*<<< orphan*/  mlx5_fc_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_ib_set_rule_source_port (struct mlx5_ib_dev*,struct mlx5_flow_spec*,struct mlx5_eswitch_rep*) ; 
 int /*<<< orphan*/  mlx5_ib_warn (struct mlx5_ib_dev*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int parse_flow_attr (int /*<<< orphan*/ ,struct mlx5_flow_spec*,void const*,struct ib_flow_attr const*,struct mlx5_flow_act*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_underlay_qp (struct mlx5_ib_dev*,struct mlx5_flow_spec*,int /*<<< orphan*/ ) ; 
 struct mlx5_ib_mcounters* to_mcounters (TYPE_3__*) ; 

__attribute__((used)) static struct mlx5_ib_flow_handler *_create_flow_rule(struct mlx5_ib_dev *dev,
						      struct mlx5_ib_flow_prio *ft_prio,
						      const struct ib_flow_attr *flow_attr,
						      struct mlx5_flow_destination *dst,
						      u32 underlay_qpn,
						      struct mlx5_ib_create_flow *ucmd)
{
	struct mlx5_flow_table	*ft = ft_prio->flow_table;
	struct mlx5_ib_flow_handler *handler;
	struct mlx5_flow_act flow_act = {};
	struct mlx5_flow_spec *spec;
	struct mlx5_flow_destination dest_arr[2] = {};
	struct mlx5_flow_destination *rule_dst = dest_arr;
	const void *ib_flow = (const void *)flow_attr + sizeof(*flow_attr);
	unsigned int spec_index;
	u32 prev_type = 0;
	int err = 0;
	int dest_num = 0;
	bool is_egress = flow_attr->flags & IB_FLOW_ATTR_FLAGS_EGRESS;

	if (!is_valid_attr(dev->mdev, flow_attr))
		return ERR_PTR(-EINVAL);

	if (dev->is_rep && is_egress)
		return ERR_PTR(-EINVAL);

	spec = kvzalloc(sizeof(*spec), GFP_KERNEL);
	handler = kzalloc(sizeof(*handler), GFP_KERNEL);
	if (!handler || !spec) {
		err = -ENOMEM;
		goto free;
	}

	INIT_LIST_HEAD(&handler->list);
	if (dst) {
		memcpy(&dest_arr[0], dst, sizeof(*dst));
		dest_num++;
	}

	for (spec_index = 0; spec_index < flow_attr->num_of_specs; spec_index++) {
		err = parse_flow_attr(dev->mdev, spec,
				      ib_flow, flow_attr, &flow_act,
				      prev_type);
		if (err < 0)
			goto free;

		prev_type = ((union ib_flow_spec *)ib_flow)->type;
		ib_flow += ((union ib_flow_spec *)ib_flow)->size;
	}

	if (!flow_is_multicast_only(flow_attr))
		set_underlay_qp(dev, spec, underlay_qpn);

	if (dev->is_rep) {
		struct mlx5_eswitch_rep *rep;

		rep = dev->port[flow_attr->port - 1].rep;
		if (!rep) {
			err = -EINVAL;
			goto free;
		}

		mlx5_ib_set_rule_source_port(dev, spec, rep);
	}

	spec->match_criteria_enable = get_match_criteria_enable(spec->match_criteria);

	if (is_egress &&
	    !is_valid_spec(dev->mdev, spec, &flow_act, is_egress)) {
		err = -EINVAL;
		goto free;
	}

	if (flow_act.action & MLX5_FLOW_CONTEXT_ACTION_COUNT) {
		struct mlx5_ib_mcounters *mcounters;

		err = flow_counters_set_data(flow_act.counters, ucmd);
		if (err)
			goto free;

		mcounters = to_mcounters(flow_act.counters);
		handler->ibcounters = flow_act.counters;
		dest_arr[dest_num].type =
			MLX5_FLOW_DESTINATION_TYPE_COUNTER;
		dest_arr[dest_num].counter_id =
			mlx5_fc_id(mcounters->hw_cntrs_hndl);
		dest_num++;
	}

	if (flow_act.action & MLX5_FLOW_CONTEXT_ACTION_DROP) {
		if (!(flow_act.action & MLX5_FLOW_CONTEXT_ACTION_COUNT)) {
			rule_dst = NULL;
			dest_num = 0;
		}
	} else {
		if (is_egress)
			flow_act.action |= MLX5_FLOW_CONTEXT_ACTION_ALLOW;
		else
			flow_act.action |=
				dest_num ?  MLX5_FLOW_CONTEXT_ACTION_FWD_DEST :
					MLX5_FLOW_CONTEXT_ACTION_FWD_NEXT_PRIO;
	}

	if ((spec->flow_context.flags & FLOW_CONTEXT_HAS_TAG)  &&
	    (flow_attr->type == IB_FLOW_ATTR_ALL_DEFAULT ||
	     flow_attr->type == IB_FLOW_ATTR_MC_DEFAULT)) {
		mlx5_ib_warn(dev, "Flow tag %u and attribute type %x isn't allowed in leftovers\n",
			     spec->flow_context.flow_tag, flow_attr->type);
		err = -EINVAL;
		goto free;
	}
	handler->rule = mlx5_add_flow_rules(ft, spec,
					    &flow_act,
					    rule_dst, dest_num);

	if (IS_ERR(handler->rule)) {
		err = PTR_ERR(handler->rule);
		goto free;
	}

	ft_prio->refcount++;
	handler->prio = ft_prio;
	handler->dev = dev;

	ft_prio->flow_table = ft;
free:
	if (err && handler) {
		if (handler->ibcounters &&
		    atomic_read(&handler->ibcounters->usecnt) == 1)
			counters_clear_description(handler->ibcounters);
		kfree(handler);
	}
	kvfree(spec);
	return err ? ERR_PTR(err) : handler;
}