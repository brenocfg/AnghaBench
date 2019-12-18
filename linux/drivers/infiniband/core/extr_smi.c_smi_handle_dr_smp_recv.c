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
struct ib_smp {scalar_t__ dr_dlid; scalar_t__ dr_slid; int /*<<< orphan*/  return_path; int /*<<< orphan*/  initial_path; int /*<<< orphan*/  hop_cnt; int /*<<< orphan*/  hop_ptr; } ;
typedef  enum smi_action { ____Placeholder_smi_action } smi_action ;

/* Variables and functions */
 scalar_t__ IB_LID_PERMISSIVE ; 
 int __smi_handle_dr_smp_recv (int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ib_get_smp_direction (struct ib_smp*) ; 

enum smi_action smi_handle_dr_smp_recv(struct ib_smp *smp, bool is_switch,
				       int port_num, int phys_port_cnt)
{
	return __smi_handle_dr_smp_recv(is_switch, port_num, phys_port_cnt,
					&smp->hop_ptr, smp->hop_cnt,
					smp->initial_path,
					smp->return_path,
					ib_get_smp_direction(smp),
					smp->dr_dlid == IB_LID_PERMISSIVE,
					smp->dr_slid == IB_LID_PERMISSIVE);
}