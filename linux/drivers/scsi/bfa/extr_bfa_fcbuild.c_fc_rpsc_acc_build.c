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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct fchs_s {int dummy; } ;
struct fc_rpsc_speed_info_s {int port_speed_cap; int port_op_speed; } ;
struct fc_rpsc_acc_s {TYPE_1__* speed_info; void* num_entries; int /*<<< orphan*/  command; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_2__ {void* port_op_speed; void* port_speed_cap; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_ELS_ACC ; 
 void* cpu_to_be16 (int) ; 
 int /*<<< orphan*/  fc_els_rsp_build (struct fchs_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct fc_rpsc_acc_s*,int /*<<< orphan*/ ,int) ; 

u16
fc_rpsc_acc_build(struct fchs_s *fchs, struct fc_rpsc_acc_s *rpsc_acc,
		u32 d_id, u32 s_id, __be16 ox_id,
		  struct fc_rpsc_speed_info_s *oper_speed)
{
	memset(rpsc_acc, 0, sizeof(struct fc_rpsc_acc_s));

	fc_els_rsp_build(fchs, d_id, s_id, ox_id);

	rpsc_acc->command = FC_ELS_ACC;
	rpsc_acc->num_entries = cpu_to_be16(1);

	rpsc_acc->speed_info[0].port_speed_cap =
		cpu_to_be16(oper_speed->port_speed_cap);

	rpsc_acc->speed_info[0].port_op_speed =
		cpu_to_be16(oper_speed->port_op_speed);

	return sizeof(struct fc_rpsc_acc_s);
}