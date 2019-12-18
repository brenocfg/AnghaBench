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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void
mlxsw_sp1_ptp_got_timestamp(struct mlxsw_sp *mlxsw_sp, bool ingress,
			    u8 local_port, u8 message_type,
			    u8 domain_number,
			    u16 sequence_id, u64 timestamp)
{
}