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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {size_t ing_types; size_t egr_types; } ;
struct mlxsw_sp_port {TYPE_1__ ptp; } ;
struct mlxsw_sp1_ptp_key {size_t local_port; size_t domain_number; size_t message_type; int ingress; int /*<<< orphan*/  sequence_id; } ;
struct mlxsw_sp {struct mlxsw_sp_port** ports; } ;
typedef  int /*<<< orphan*/  key ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct mlxsw_sp1_ptp_key*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlxsw_sp1_ptp_got_piece (struct mlxsw_sp*,struct mlxsw_sp1_ptp_key,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void mlxsw_sp1_ptp_got_timestamp(struct mlxsw_sp *mlxsw_sp, bool ingress,
				 u8 local_port, u8 message_type,
				 u8 domain_number, u16 sequence_id,
				 u64 timestamp)
{
	struct mlxsw_sp_port *mlxsw_sp_port;
	struct mlxsw_sp1_ptp_key key;
	u8 types;

	mlxsw_sp_port = mlxsw_sp->ports[local_port];
	if (!mlxsw_sp_port)
		return;

	types = ingress ? mlxsw_sp_port->ptp.ing_types :
			  mlxsw_sp_port->ptp.egr_types;

	/* For message types whose timestamping was not enabled on this port,
	 * don't bother with the timestamp.
	 */
	if (!((1 << message_type) & types))
		return;

	memset(&key, 0, sizeof(key));
	key.local_port = local_port;
	key.domain_number = domain_number;
	key.message_type = message_type;
	key.sequence_id = sequence_id;
	key.ingress = ingress;

	mlxsw_sp1_ptp_got_piece(mlxsw_sp, key, NULL, timestamp);
}