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
struct team {int dummy; } ;
struct sk_buff {int dummy; } ;
struct genl_info {int /*<<< orphan*/  snd_seq; int /*<<< orphan*/  snd_portid; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NLM_F_ACK ; 
 int team_nl_send_port_list_get (struct team*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  team_nl_send_unicast ; 
 struct team* team_nl_team_get (struct genl_info*) ; 
 int /*<<< orphan*/  team_nl_team_put (struct team*) ; 

__attribute__((used)) static int team_nl_cmd_port_list_get(struct sk_buff *skb,
				     struct genl_info *info)
{
	struct team *team;
	int err;

	team = team_nl_team_get(info);
	if (!team)
		return -EINVAL;

	err = team_nl_send_port_list_get(team, info->snd_portid, info->snd_seq,
					 NLM_F_ACK, team_nl_send_unicast, NULL);

	team_nl_team_put(team);

	return err;
}