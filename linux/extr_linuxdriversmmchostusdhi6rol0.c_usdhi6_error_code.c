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
typedef  scalar_t__ u32 ;
struct usdhi6_host {int io_error; TYPE_2__* mrq; int /*<<< orphan*/  wait; int /*<<< orphan*/  mmc; } ;
struct TYPE_4__ {TYPE_1__* cmd; } ;
struct TYPE_3__ {int opcode; } ;

/* Variables and functions */
 int EILSEQ ; 
 int EIO ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  USDHI6_SD_ERR_STS1 ; 
 scalar_t__ USDHI6_SD_ERR_STS1_CRC_NO_ERROR ; 
 int /*<<< orphan*/  USDHI6_SD_ERR_STS2 ; 
 int USDHI6_SD_INFO2_ILA ; 
 int USDHI6_SD_INFO2_RSP_TOUT ; 
 int USDHI6_SD_INFO2_TOUT ; 
 int /*<<< orphan*/  USDHI6_SD_RSP54 ; 
 int /*<<< orphan*/  USDHI6_SD_STOP ; 
 int /*<<< orphan*/  USDHI6_SD_STOP_STP ; 
 int /*<<< orphan*/  USDHI6_WAIT_FOR_CMD ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,int,...) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 scalar_t__ usdhi6_read (struct usdhi6_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usdhi6_write (struct usdhi6_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usdhi6_error_code(struct usdhi6_host *host)
{
	u32 err;

	usdhi6_write(host, USDHI6_SD_STOP, USDHI6_SD_STOP_STP);

	if (host->io_error &
	    (USDHI6_SD_INFO2_RSP_TOUT | USDHI6_SD_INFO2_TOUT)) {
		u32 rsp54 = usdhi6_read(host, USDHI6_SD_RSP54);
		int opc = host->mrq ? host->mrq->cmd->opcode : -1;

		err = usdhi6_read(host, USDHI6_SD_ERR_STS2);
		/* Response timeout is often normal, don't spam the log */
		if (host->wait == USDHI6_WAIT_FOR_CMD)
			dev_dbg(mmc_dev(host->mmc),
				"T-out sts 0x%x, resp 0x%x, state %u, CMD%d\n",
				err, rsp54, host->wait, opc);
		else
			dev_warn(mmc_dev(host->mmc),
				 "T-out sts 0x%x, resp 0x%x, state %u, CMD%d\n",
				 err, rsp54, host->wait, opc);
		return -ETIMEDOUT;
	}

	err = usdhi6_read(host, USDHI6_SD_ERR_STS1);
	if (err != USDHI6_SD_ERR_STS1_CRC_NO_ERROR)
		dev_warn(mmc_dev(host->mmc), "Err sts 0x%x, state %u, CMD%d\n",
			 err, host->wait, host->mrq ? host->mrq->cmd->opcode : -1);
	if (host->io_error & USDHI6_SD_INFO2_ILA)
		return -EILSEQ;

	return -EIO;
}