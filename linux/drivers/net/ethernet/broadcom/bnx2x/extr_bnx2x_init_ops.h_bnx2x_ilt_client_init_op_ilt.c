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
struct ilt_client_info {int flags; int start; int end; } ;
struct bnx2x_ilt {int /*<<< orphan*/  start_line; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int ILT_CLIENT_SKIP_INIT ; 
 int /*<<< orphan*/  bnx2x_ilt_boundry_init_op (struct bnx2x*,struct ilt_client_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_ilt_line_init_op (struct bnx2x*,struct bnx2x_ilt*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnx2x_ilt_client_init_op_ilt(struct bnx2x *bp,
					 struct bnx2x_ilt *ilt,
					 struct ilt_client_info *ilt_cli,
					 u8 initop)
{
	int i;

	if (ilt_cli->flags & ILT_CLIENT_SKIP_INIT)
		return;

	for (i = ilt_cli->start; i <= ilt_cli->end; i++)
		bnx2x_ilt_line_init_op(bp, ilt, i, initop);

	/* init/clear the ILT boundries */
	bnx2x_ilt_boundry_init_op(bp, ilt_cli, ilt->start_line, initop);
}