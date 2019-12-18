#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int SUE; int /*<<< orphan*/  SCSI; } ;
union wd719x_regs {TYPE_4__ bytes; } ;
struct wd719x_scb {TYPE_2__* cmd; } ;
struct wd719x {TYPE_3__* pdev; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {TYPE_1__* device; } ;
struct TYPE_5__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int DID_ABORT ; 
 int DID_ERROR ; 
 int DID_NO_CONNECT ; 
 int DID_OK ; 
 int DID_PARITY ; 
 int DID_RESET ; 
 int DID_TIME_OUT ; 
#define  WD719X_SUE_ARSDONE 147 
#define  WD719X_SUE_BADPHASE 146 
#define  WD719X_SUE_BADTAGS 145 
#define  WD719X_SUE_BUSERROR 144 
#define  WD719X_SUE_BUSFREE 143 
#define  WD719X_SUE_CHAN1ABORT 142 
#define  WD719X_SUE_CHAN1PAR 141 
#define  WD719X_SUE_CHAN23ABORT 140 
#define  WD719X_SUE_CHAN23PAR 139 
#define  WD719X_SUE_IGNORED 138 
#define  WD719X_SUE_NOERRORS 137 
#define  WD719X_SUE_NOSCAMID 136 
#define  WD719X_SUE_REJECTED 135 
#define  WD719X_SUE_RESET 134 
#define  WD719X_SUE_SCBQFULL 133 
#define  WD719X_SUE_TERM 132 
#define  WD719X_SUE_TIMEOUT 131 
#define  WD719X_SUE_TOOLONG 130 
#define  WD719X_SUE_WRONGTAGS 129 
#define  WD719X_SUE_WRONGWAY 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  wd719x_finish_cmd (struct wd719x_scb*,int) ; 

__attribute__((used)) static inline void wd719x_interrupt_SCB(struct wd719x *wd,
					union wd719x_regs regs,
					struct wd719x_scb *scb)
{
	int result;

	/* now have to find result from card */
	switch (regs.bytes.SUE) {
	case WD719X_SUE_NOERRORS:
		result = DID_OK;
		break;
	case WD719X_SUE_REJECTED:
		dev_err(&wd->pdev->dev, "command rejected\n");
		result = DID_ERROR;
		break;
	case WD719X_SUE_SCBQFULL:
		dev_err(&wd->pdev->dev, "SCB queue is full\n");
		result = DID_ERROR;
		break;
	case WD719X_SUE_TERM:
		dev_dbg(&wd->pdev->dev, "SCB terminated by direct command\n");
		result = DID_ABORT;	/* or DID_RESET? */
		break;
	case WD719X_SUE_CHAN1ABORT:
	case WD719X_SUE_CHAN23ABORT:
		result = DID_ABORT;
		dev_err(&wd->pdev->dev, "DMA abort\n");
		break;
	case WD719X_SUE_CHAN1PAR:
	case WD719X_SUE_CHAN23PAR:
		result = DID_PARITY;
		dev_err(&wd->pdev->dev, "DMA parity error\n");
		break;
	case WD719X_SUE_TIMEOUT:
		result = DID_TIME_OUT;
		dev_dbg(&wd->pdev->dev, "selection timeout\n");
		break;
	case WD719X_SUE_RESET:
		dev_dbg(&wd->pdev->dev, "bus reset occurred\n");
		result = DID_RESET;
		break;
	case WD719X_SUE_BUSERROR:
		dev_dbg(&wd->pdev->dev, "SCSI bus error\n");
		result = DID_ERROR;
		break;
	case WD719X_SUE_WRONGWAY:
		dev_err(&wd->pdev->dev, "wrong data transfer direction\n");
		result = DID_ERROR;
		break;
	case WD719X_SUE_BADPHASE:
		dev_err(&wd->pdev->dev, "invalid SCSI phase\n");
		result = DID_ERROR;
		break;
	case WD719X_SUE_TOOLONG:
		dev_err(&wd->pdev->dev, "record too long\n");
		result = DID_ERROR;
		break;
	case WD719X_SUE_BUSFREE:
		dev_err(&wd->pdev->dev, "unexpected bus free\n");
		result = DID_NO_CONNECT; /* or DID_ERROR ???*/
		break;
	case WD719X_SUE_ARSDONE:
		dev_dbg(&wd->pdev->dev, "auto request sense\n");
		if (regs.bytes.SCSI == 0)
			result = DID_OK;
		else
			result = DID_PARITY;
		break;
	case WD719X_SUE_IGNORED:
		dev_err(&wd->pdev->dev, "target id %d ignored command\n",
			scb->cmd->device->id);
		result = DID_NO_CONNECT;
		break;
	case WD719X_SUE_WRONGTAGS:
		dev_err(&wd->pdev->dev, "reversed tags\n");
		result = DID_ERROR;
		break;
	case WD719X_SUE_BADTAGS:
		dev_err(&wd->pdev->dev, "tag type not supported by target\n");
		result = DID_ERROR;
		break;
	case WD719X_SUE_NOSCAMID:
		dev_err(&wd->pdev->dev, "no SCAM soft ID available\n");
		result = DID_ERROR;
		break;
	default:
		dev_warn(&wd->pdev->dev, "unknown SUE error code: 0x%x\n",
			 regs.bytes.SUE);
		result = DID_ERROR;
		break;
	}

	wd719x_finish_cmd(scb, result);
}