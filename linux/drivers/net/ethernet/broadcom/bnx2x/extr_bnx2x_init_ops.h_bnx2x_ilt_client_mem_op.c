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
struct ilt_client_info {int flags; int start; int end; int /*<<< orphan*/  page_size; } ;
struct bnx2x_ilt {int /*<<< orphan*/ * lines; struct ilt_client_info* clients; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 struct bnx2x_ilt* BP_ILT (struct bnx2x*) ; 
 int ILT_CLIENT_SKIP_INIT ; 
 int ILT_CLIENT_SKIP_MEM ; 
 int bnx2x_ilt_line_mem_op (struct bnx2x*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bnx2x_ilt_client_mem_op(struct bnx2x *bp, int cli_num,
				   u8 memop)
{
	int i, rc;
	struct bnx2x_ilt *ilt = BP_ILT(bp);
	struct ilt_client_info *ilt_cli = &ilt->clients[cli_num];

	if (!ilt || !ilt->lines)
		return -1;

	if (ilt_cli->flags & (ILT_CLIENT_SKIP_INIT | ILT_CLIENT_SKIP_MEM))
		return 0;

	for (rc = 0, i = ilt_cli->start; i <= ilt_cli->end && !rc; i++) {
		rc = bnx2x_ilt_line_mem_op(bp, &ilt->lines[i],
					   ilt_cli->page_size, memop);
	}
	return rc;
}