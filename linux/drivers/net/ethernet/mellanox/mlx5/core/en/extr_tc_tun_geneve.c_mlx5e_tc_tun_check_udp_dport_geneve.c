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
struct netlink_ext_ack {int dummy; } ;
struct mlx5e_priv {int /*<<< orphan*/  netdev; } ;
struct flow_rule {int dummy; } ;
struct flow_match_ports {TYPE_2__* key; } ;
struct TYPE_3__ {struct netlink_ext_ack* extack; } ;
struct flow_cls_offload {TYPE_1__ common; } ;
struct TYPE_4__ {int /*<<< orphan*/  dst; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_ENC_PORTS ; 
 scalar_t__ GENEVE_UDP_PORT ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 struct flow_rule* flow_cls_offload_flow_rule (struct flow_cls_offload*) ; 
 int /*<<< orphan*/  flow_rule_match_enc_ports (struct flow_rule*,struct flow_match_ports*) ; 
 int /*<<< orphan*/  flow_rule_match_key (struct flow_rule*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static int mlx5e_tc_tun_check_udp_dport_geneve(struct mlx5e_priv *priv,
					       struct flow_cls_offload *f)
{
	struct flow_rule *rule = flow_cls_offload_flow_rule(f);
	struct netlink_ext_ack *extack = f->common.extack;
	struct flow_match_ports enc_ports;

	if (!flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_ENC_PORTS))
		return -EOPNOTSUPP;

	flow_rule_match_enc_ports(rule, &enc_ports);

	/* Currently we support only default GENEVE
	 * port, so udp dst port must match.
	 */
	if (be16_to_cpu(enc_ports.key->dst) != GENEVE_UDP_PORT) {
		NL_SET_ERR_MSG_MOD(extack,
				   "Matched UDP dst port is not registered as a GENEVE port");
		netdev_warn(priv->netdev,
			    "UDP port %d is not registered as a GENEVE port\n",
			    be16_to_cpu(enc_ports.key->dst));
		return -EOPNOTSUPP;
	}

	return 0;
}