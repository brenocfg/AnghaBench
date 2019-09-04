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
struct fdp1_dev {int dummy; } ;
struct fdp1_ctx {struct fdp1_dev* fdp1; } ;

/* Variables and functions */
 int /*<<< orphan*/  FD1_IPC_COMB_DET ; 
 int /*<<< orphan*/  FD1_IPC_COMB_DET_CONST ; 
 int /*<<< orphan*/  FD1_IPC_DLI_ANGLE ; 
 int /*<<< orphan*/  FD1_IPC_DLI_ANGLE_CONST ; 
 int /*<<< orphan*/  FD1_IPC_DLI_BLEND ; 
 int /*<<< orphan*/  FD1_IPC_DLI_BLEND_CONST ; 
 int /*<<< orphan*/  FD1_IPC_DLI_HGAIN ; 
 int /*<<< orphan*/  FD1_IPC_DLI_HGAIN_CONST ; 
 int /*<<< orphan*/  FD1_IPC_DLI_ISOPIX0 ; 
 int /*<<< orphan*/  FD1_IPC_DLI_ISOPIX0_CONST ; 
 int /*<<< orphan*/  FD1_IPC_DLI_ISOPIX1 ; 
 int /*<<< orphan*/  FD1_IPC_DLI_ISOPIX1_CONST ; 
 int /*<<< orphan*/  FD1_IPC_DLI_SPRS ; 
 int /*<<< orphan*/  FD1_IPC_DLI_SPRS_CONST ; 
 int /*<<< orphan*/  FD1_IPC_MOTDEC ; 
 int /*<<< orphan*/  FD1_IPC_MOTDEC_CONST ; 
 int /*<<< orphan*/  FD1_IPC_SMSK_THRESH ; 
 int /*<<< orphan*/  FD1_IPC_SMSK_THRESH_CONST ; 
 int /*<<< orphan*/  fdp1_write (struct fdp1_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fdp1_set_ipc_dli(struct fdp1_ctx *ctx)
{
	struct fdp1_dev *fdp1 = ctx->fdp1;

	fdp1_write(fdp1, FD1_IPC_SMSK_THRESH_CONST,	FD1_IPC_SMSK_THRESH);
	fdp1_write(fdp1, FD1_IPC_COMB_DET_CONST,	FD1_IPC_COMB_DET);
	fdp1_write(fdp1, FD1_IPC_MOTDEC_CONST,	FD1_IPC_MOTDEC);

	fdp1_write(fdp1, FD1_IPC_DLI_BLEND_CONST,	FD1_IPC_DLI_BLEND);
	fdp1_write(fdp1, FD1_IPC_DLI_HGAIN_CONST,	FD1_IPC_DLI_HGAIN);
	fdp1_write(fdp1, FD1_IPC_DLI_SPRS_CONST,	FD1_IPC_DLI_SPRS);
	fdp1_write(fdp1, FD1_IPC_DLI_ANGLE_CONST,	FD1_IPC_DLI_ANGLE);
	fdp1_write(fdp1, FD1_IPC_DLI_ISOPIX0_CONST,	FD1_IPC_DLI_ISOPIX0);
	fdp1_write(fdp1, FD1_IPC_DLI_ISOPIX1_CONST,	FD1_IPC_DLI_ISOPIX1);
}