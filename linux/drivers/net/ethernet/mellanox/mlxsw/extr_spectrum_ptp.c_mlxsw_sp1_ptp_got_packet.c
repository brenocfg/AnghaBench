#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {size_t ing_types; size_t egr_types; } ;
struct mlxsw_sp_port {TYPE_1__ ptp; } ;
struct mlxsw_sp1_ptp_key {size_t local_port; int ingress; int message_type; int /*<<< orphan*/  sequence_id; int /*<<< orphan*/  domain_number; } ;
struct mlxsw_sp {struct mlxsw_sp_port** ports; } ;
typedef  int /*<<< orphan*/  key ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct mlxsw_sp1_ptp_key*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlxsw_sp1_ptp_got_piece (struct mlxsw_sp*,struct mlxsw_sp1_ptp_key,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp1_ptp_packet_finish (struct mlxsw_sp*,struct sk_buff*,size_t,int,int /*<<< orphan*/ *) ; 
 int mlxsw_sp_ptp_parse (struct sk_buff*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlxsw_sp1_ptp_got_packet(struct mlxsw_sp *mlxsw_sp,
				     struct sk_buff *skb, u8 local_port,
				     bool ingress)
{
	struct mlxsw_sp_port *mlxsw_sp_port;
	struct mlxsw_sp1_ptp_key key;
	u8 types;
	int err;

	mlxsw_sp_port = mlxsw_sp->ports[local_port];
	if (!mlxsw_sp_port)
		goto immediate;

	types = ingress ? mlxsw_sp_port->ptp.ing_types :
			  mlxsw_sp_port->ptp.egr_types;
	if (!types)
		goto immediate;

	memset(&key, 0, sizeof(key));
	key.local_port = local_port;
	key.ingress = ingress;

	err = mlxsw_sp_ptp_parse(skb, &key.domain_number, &key.message_type,
				 &key.sequence_id);
	if (err)
		goto immediate;

	/* For packets whose timestamping was not enabled on this port, don't
	 * bother trying to match the timestamp.
	 */
	if (!((1 << key.message_type) & types))
		goto immediate;

	mlxsw_sp1_ptp_got_piece(mlxsw_sp, key, skb, 0);
	return;

immediate:
	mlxsw_sp1_ptp_packet_finish(mlxsw_sp, skb, local_port, ingress, NULL);
}