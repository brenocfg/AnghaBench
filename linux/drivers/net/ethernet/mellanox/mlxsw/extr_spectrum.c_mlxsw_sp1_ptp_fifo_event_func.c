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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int mlxsw_reg_mtpptr_local_port_get (char*) ; 
 int mlxsw_reg_mtpptr_num_rec_get (char*) ; 
 int /*<<< orphan*/  mlxsw_reg_mtpptr_unpack (char*,int,int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp1_ptp_got_timestamp (struct mlxsw_sp*,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlxsw_sp1_ptp_fifo_event_func(struct mlxsw_sp *mlxsw_sp,
					  char *mtpptr_pl, bool ingress)
{
	u8 local_port;
	u8 num_rec;
	int i;

	local_port = mlxsw_reg_mtpptr_local_port_get(mtpptr_pl);
	num_rec = mlxsw_reg_mtpptr_num_rec_get(mtpptr_pl);
	for (i = 0; i < num_rec; i++) {
		u8 domain_number;
		u8 message_type;
		u16 sequence_id;
		u64 timestamp;

		mlxsw_reg_mtpptr_unpack(mtpptr_pl, i, &message_type,
					&domain_number, &sequence_id,
					&timestamp);
		mlxsw_sp1_ptp_got_timestamp(mlxsw_sp, ingress, local_port,
					    message_type, domain_number,
					    sequence_id, timestamp);
	}
}