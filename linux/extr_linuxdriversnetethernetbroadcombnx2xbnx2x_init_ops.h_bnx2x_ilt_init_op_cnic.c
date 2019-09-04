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
struct bnx2x {int dummy; } ;

/* Variables and functions */
 scalar_t__ CONFIGURE_NIC_MODE (struct bnx2x*) ; 
 int /*<<< orphan*/  ILT_CLIENT_SRC ; 
 int /*<<< orphan*/  ILT_CLIENT_TM ; 
 int /*<<< orphan*/  bnx2x_ilt_client_id_init_op (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnx2x_ilt_init_op_cnic(struct bnx2x *bp, u8 initop)
{
	if (CONFIGURE_NIC_MODE(bp))
		bnx2x_ilt_client_id_init_op(bp, ILT_CLIENT_SRC, initop);
	bnx2x_ilt_client_id_init_op(bp, ILT_CLIENT_TM, initop);
}