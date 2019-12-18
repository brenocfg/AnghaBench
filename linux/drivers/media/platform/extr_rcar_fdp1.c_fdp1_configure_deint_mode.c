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
typedef  int u32 ;
struct fdp1_job {int dummy; } ;
struct fdp1_dev {int dummy; } ;
struct fdp1_ctx {int deint_mode; int sequence; int /*<<< orphan*/  aborting; struct fdp1_dev* fdp1; } ;

/* Variables and functions */
 int /*<<< orphan*/  FD1_CTL_CHACT ; 
 int FD1_CTL_CHACT_RD0 ; 
 int FD1_CTL_CHACT_RD1 ; 
 int FD1_CTL_CHACT_RD2 ; 
 int FD1_CTL_CHACT_SMR ; 
 int FD1_CTL_CHACT_SMW ; 
 int FD1_CTL_CHACT_WR ; 
 int /*<<< orphan*/  FD1_CTL_OPMODE ; 
 int FD1_CTL_OPMODE_PRG ; 
 int FD1_CTL_OPMODE_VIMD_NOINTERRUPT ; 
 int /*<<< orphan*/  FD1_IPC_MODE ; 
 int FD1_IPC_MODE_DIM_ADAPT2D3D ; 
 int FD1_IPC_MODE_DIM_FIXED2D ; 
 int FD1_IPC_MODE_DIM_FIXED3D ; 
 int FD1_IPC_MODE_DIM_NEXTFIELD ; 
 int FD1_IPC_MODE_DIM_PREVFIELD ; 
 int FD1_IPC_MODE_DLI ; 
#define  FDP1_ADAPT2D3D 133 
#define  FDP1_FIXED2D 132 
#define  FDP1_FIXED3D 131 
#define  FDP1_NEXTFIELD 130 
#define  FDP1_PREVFIELD 129 
#define  FDP1_PROGRESSIVE 128 
 int /*<<< orphan*/  dprintk (struct fdp1_dev*,char*) ; 
 int /*<<< orphan*/  fdp1_write (struct fdp1_dev*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fdp1_configure_deint_mode(struct fdp1_ctx *ctx,
				      struct fdp1_job *job)
{
	struct fdp1_dev *fdp1 = ctx->fdp1;
	u32 opmode = FD1_CTL_OPMODE_VIMD_NOINTERRUPT;
	u32 ipcmode = FD1_IPC_MODE_DLI; /* Always set */
	u32 channels = FD1_CTL_CHACT_WR | FD1_CTL_CHACT_RD1; /* Always on */

	/* De-interlacing Mode */
	switch (ctx->deint_mode) {
	default:
	case FDP1_PROGRESSIVE:
		dprintk(fdp1, "Progressive Mode\n");
		opmode |= FD1_CTL_OPMODE_PRG;
		ipcmode |= FD1_IPC_MODE_DIM_FIXED2D;
		break;
	case FDP1_ADAPT2D3D:
		dprintk(fdp1, "Adapt2D3D Mode\n");
		if (ctx->sequence == 0 || ctx->aborting)
			ipcmode |= FD1_IPC_MODE_DIM_FIXED2D;
		else
			ipcmode |= FD1_IPC_MODE_DIM_ADAPT2D3D;

		if (ctx->sequence > 1) {
			channels |= FD1_CTL_CHACT_SMW;
			channels |= FD1_CTL_CHACT_RD0 | FD1_CTL_CHACT_RD2;
		}

		if (ctx->sequence > 2)
			channels |= FD1_CTL_CHACT_SMR;

		break;
	case FDP1_FIXED3D:
		dprintk(fdp1, "Fixed 3D Mode\n");
		ipcmode |= FD1_IPC_MODE_DIM_FIXED3D;
		/* Except for first and last frame, enable all channels */
		if (!(ctx->sequence == 0 || ctx->aborting))
			channels |= FD1_CTL_CHACT_RD0 | FD1_CTL_CHACT_RD2;
		break;
	case FDP1_FIXED2D:
		dprintk(fdp1, "Fixed 2D Mode\n");
		ipcmode |= FD1_IPC_MODE_DIM_FIXED2D;
		/* No extra channels enabled */
		break;
	case FDP1_PREVFIELD:
		dprintk(fdp1, "Previous Field Mode\n");
		ipcmode |= FD1_IPC_MODE_DIM_PREVFIELD;
		channels |= FD1_CTL_CHACT_RD0; /* Previous */
		break;
	case FDP1_NEXTFIELD:
		dprintk(fdp1, "Next Field Mode\n");
		ipcmode |= FD1_IPC_MODE_DIM_NEXTFIELD;
		channels |= FD1_CTL_CHACT_RD2; /* Next */
		break;
	}

	fdp1_write(fdp1, channels,	FD1_CTL_CHACT);
	fdp1_write(fdp1, opmode,	FD1_CTL_OPMODE);
	fdp1_write(fdp1, ipcmode,	FD1_IPC_MODE);
}