#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct team_option_inst_info {int /*<<< orphan*/  array_index; TYPE_2__* port; } ;
struct team_option_inst {int changed; scalar_t__ removed; struct team_option* option; struct team_option_inst_info info; } ;
struct team_option {int type; scalar_t__ array_size; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int /*<<< orphan*/  ptr; int /*<<< orphan*/  len; } ;
struct TYPE_8__ {int /*<<< orphan*/  s32_val; int /*<<< orphan*/  bool_val; TYPE_3__ bin_val; int /*<<< orphan*/  str_val; int /*<<< orphan*/  u32_val; } ;
struct team_gsetter_ctx {TYPE_4__ data; struct team_option_inst_info* info; } ;
struct team {int dummy; } ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct TYPE_6__ {TYPE_1__* dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  ifindex; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int EMSGSIZE ; 
 int /*<<< orphan*/  NLA_BINARY ; 
 int /*<<< orphan*/  NLA_FLAG ; 
 int /*<<< orphan*/  NLA_S32 ; 
 int /*<<< orphan*/  NLA_STRING ; 
 int /*<<< orphan*/  NLA_U32 ; 
 int /*<<< orphan*/  TEAM_ATTR_ITEM_OPTION ; 
 int /*<<< orphan*/  TEAM_ATTR_OPTION_ARRAY_INDEX ; 
 int /*<<< orphan*/  TEAM_ATTR_OPTION_CHANGED ; 
 int /*<<< orphan*/  TEAM_ATTR_OPTION_DATA ; 
 int /*<<< orphan*/  TEAM_ATTR_OPTION_NAME ; 
 int /*<<< orphan*/  TEAM_ATTR_OPTION_PORT_IFINDEX ; 
 int /*<<< orphan*/  TEAM_ATTR_OPTION_REMOVED ; 
 int /*<<< orphan*/  TEAM_ATTR_OPTION_TYPE ; 
#define  TEAM_OPTION_TYPE_BINARY 132 
#define  TEAM_OPTION_TYPE_BOOL 131 
#define  TEAM_OPTION_TYPE_S32 130 
#define  TEAM_OPTION_TYPE_STRING 129 
#define  TEAM_OPTION_TYPE_U32 128 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_flag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_put_s32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int team_option_get (struct team*,struct team_option_inst*,struct team_gsetter_ctx*) ; 

__attribute__((used)) static int team_nl_fill_one_option_get(struct sk_buff *skb, struct team *team,
				       struct team_option_inst *opt_inst)
{
	struct nlattr *option_item;
	struct team_option *option = opt_inst->option;
	struct team_option_inst_info *opt_inst_info = &opt_inst->info;
	struct team_gsetter_ctx ctx;
	int err;

	ctx.info = opt_inst_info;
	err = team_option_get(team, opt_inst, &ctx);
	if (err)
		return err;

	option_item = nla_nest_start_noflag(skb, TEAM_ATTR_ITEM_OPTION);
	if (!option_item)
		return -EMSGSIZE;

	if (nla_put_string(skb, TEAM_ATTR_OPTION_NAME, option->name))
		goto nest_cancel;
	if (opt_inst_info->port &&
	    nla_put_u32(skb, TEAM_ATTR_OPTION_PORT_IFINDEX,
			opt_inst_info->port->dev->ifindex))
		goto nest_cancel;
	if (opt_inst->option->array_size &&
	    nla_put_u32(skb, TEAM_ATTR_OPTION_ARRAY_INDEX,
			opt_inst_info->array_index))
		goto nest_cancel;

	switch (option->type) {
	case TEAM_OPTION_TYPE_U32:
		if (nla_put_u8(skb, TEAM_ATTR_OPTION_TYPE, NLA_U32))
			goto nest_cancel;
		if (nla_put_u32(skb, TEAM_ATTR_OPTION_DATA, ctx.data.u32_val))
			goto nest_cancel;
		break;
	case TEAM_OPTION_TYPE_STRING:
		if (nla_put_u8(skb, TEAM_ATTR_OPTION_TYPE, NLA_STRING))
			goto nest_cancel;
		if (nla_put_string(skb, TEAM_ATTR_OPTION_DATA,
				   ctx.data.str_val))
			goto nest_cancel;
		break;
	case TEAM_OPTION_TYPE_BINARY:
		if (nla_put_u8(skb, TEAM_ATTR_OPTION_TYPE, NLA_BINARY))
			goto nest_cancel;
		if (nla_put(skb, TEAM_ATTR_OPTION_DATA, ctx.data.bin_val.len,
			    ctx.data.bin_val.ptr))
			goto nest_cancel;
		break;
	case TEAM_OPTION_TYPE_BOOL:
		if (nla_put_u8(skb, TEAM_ATTR_OPTION_TYPE, NLA_FLAG))
			goto nest_cancel;
		if (ctx.data.bool_val &&
		    nla_put_flag(skb, TEAM_ATTR_OPTION_DATA))
			goto nest_cancel;
		break;
	case TEAM_OPTION_TYPE_S32:
		if (nla_put_u8(skb, TEAM_ATTR_OPTION_TYPE, NLA_S32))
			goto nest_cancel;
		if (nla_put_s32(skb, TEAM_ATTR_OPTION_DATA, ctx.data.s32_val))
			goto nest_cancel;
		break;
	default:
		BUG();
	}
	if (opt_inst->removed && nla_put_flag(skb, TEAM_ATTR_OPTION_REMOVED))
		goto nest_cancel;
	if (opt_inst->changed) {
		if (nla_put_flag(skb, TEAM_ATTR_OPTION_CHANGED))
			goto nest_cancel;
		opt_inst->changed = false;
	}
	nla_nest_end(skb, option_item);
	return 0;

nest_cancel:
	nla_nest_cancel(skb, option_item);
	return -EMSGSIZE;
}