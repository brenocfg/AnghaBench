#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sh_mmcif_host {int /*<<< orphan*/  wait_for; } ;
struct mmc_request {TYPE_2__* stop; TYPE_1__* cmd; } ;
struct device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  error; } ;
struct TYPE_3__ {int opcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  MASK_MCMD12DRE ; 
 int /*<<< orphan*/  MASK_MCMD12RBE ; 
 int /*<<< orphan*/  MMCIF_CE_INT_MASK ; 
 int /*<<< orphan*/  MMCIF_WAIT_FOR_STOP ; 
#define  MMC_READ_MULTIPLE_BLOCK 129 
#define  MMC_WRITE_MULTIPLE_BLOCK 128 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  sh_mmcif_bitset (struct sh_mmcif_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh_mmcif_error_manage (struct sh_mmcif_host*) ; 
 struct device* sh_mmcif_host_to_dev (struct sh_mmcif_host*) ; 

__attribute__((used)) static void sh_mmcif_stop_cmd(struct sh_mmcif_host *host,
			      struct mmc_request *mrq)
{
	struct device *dev = sh_mmcif_host_to_dev(host);

	switch (mrq->cmd->opcode) {
	case MMC_READ_MULTIPLE_BLOCK:
		sh_mmcif_bitset(host, MMCIF_CE_INT_MASK, MASK_MCMD12DRE);
		break;
	case MMC_WRITE_MULTIPLE_BLOCK:
		sh_mmcif_bitset(host, MMCIF_CE_INT_MASK, MASK_MCMD12RBE);
		break;
	default:
		dev_err(dev, "unsupported stop cmd\n");
		mrq->stop->error = sh_mmcif_error_manage(host);
		return;
	}

	host->wait_for = MMCIF_WAIT_FOR_STOP;
}