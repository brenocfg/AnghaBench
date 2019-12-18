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
typedef  scalar_t__ u16 ;
struct i40iw_qp_flush_info {int userflushcode; } ;
typedef  enum i40iw_flush_opcode { ____Placeholder_i40iw_flush_opcode } i40iw_flush_opcode ;

/* Variables and functions */
 scalar_t__ CQE_MAJOR_DRV ; 
 scalar_t__ i40iw_get_ib_wc (int) ; 

__attribute__((used)) static void i40iw_set_flush_info(struct i40iw_qp_flush_info *pinfo,
				 u16 *min,
				 u16 *maj,
				 enum i40iw_flush_opcode opcode)
{
	*min = (u16)i40iw_get_ib_wc(opcode);
	*maj = CQE_MAJOR_DRV;
	pinfo->userflushcode = true;
}