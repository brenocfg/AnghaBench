#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_8__ {int resp_needed; int len; int /*<<< orphan*/  cmd; int /*<<< orphan*/  type; } ;
struct TYPE_9__ {TYPE_1__ s; scalar_t__ u64; } ;
struct octeon_mbox_cmd {int /*<<< orphan*/ * fn_arg; scalar_t__ fn; scalar_t__ recv_status; scalar_t__ recv_len; scalar_t__ q_no; scalar_t__* data; TYPE_2__ msg; } ;
struct TYPE_14__ {int /*<<< orphan*/  pkind; } ;
struct octeon_device {size_t num_iqs; TYPE_7__ pfvf_hsword; TYPE_6__* pci_dev; TYPE_5__** instr_queue; } ;
struct lio_version {int /*<<< orphan*/  micro; int /*<<< orphan*/  minor; void* major; } ;
typedef  scalar_t__ octeon_mbox_callback_t ;
typedef  int /*<<< orphan*/  atomic_t ;
struct TYPE_13__ {int /*<<< orphan*/  dev; } ;
struct TYPE_10__ {int /*<<< orphan*/  pkind; } ;
struct TYPE_11__ {TYPE_3__ s; } ;
struct TYPE_12__ {TYPE_4__ txpciq; } ;

/* Variables and functions */
 void* LIQUIDIO_BASE_MAJOR_VERSION ; 
 int /*<<< orphan*/  LIQUIDIO_BASE_MICRO_VERSION ; 
 int /*<<< orphan*/  LIQUIDIO_BASE_MINOR_VERSION ; 
 int /*<<< orphan*/  OCTEON_MBOX_REQUEST ; 
 int /*<<< orphan*/  OCTEON_VF_ACTIVE ; 
 size_t atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  octeon_mbox_write (struct octeon_device*,struct octeon_mbox_cmd*) ; 
 scalar_t__ octeon_pfvf_hs_callback ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 

int cn23xx_octeon_pfvf_handshake(struct octeon_device *oct)
{
	struct octeon_mbox_cmd mbox_cmd;
	u32 q_no, count = 0;
	atomic_t status;
	u32 pfmajor;
	u32 vfmajor;
	u32 ret;

	/* Sending VF_ACTIVE indication to the PF driver */
	dev_dbg(&oct->pci_dev->dev, "requesting info from pf\n");

	mbox_cmd.msg.u64 = 0;
	mbox_cmd.msg.s.type = OCTEON_MBOX_REQUEST;
	mbox_cmd.msg.s.resp_needed = 1;
	mbox_cmd.msg.s.cmd = OCTEON_VF_ACTIVE;
	mbox_cmd.msg.s.len = 2;
	mbox_cmd.data[0] = 0;
	((struct lio_version *)&mbox_cmd.data[0])->major =
						LIQUIDIO_BASE_MAJOR_VERSION;
	((struct lio_version *)&mbox_cmd.data[0])->minor =
						LIQUIDIO_BASE_MINOR_VERSION;
	((struct lio_version *)&mbox_cmd.data[0])->micro =
						LIQUIDIO_BASE_MICRO_VERSION;
	mbox_cmd.q_no = 0;
	mbox_cmd.recv_len = 0;
	mbox_cmd.recv_status = 0;
	mbox_cmd.fn = (octeon_mbox_callback_t)octeon_pfvf_hs_callback;
	mbox_cmd.fn_arg = &status;

	octeon_mbox_write(oct, &mbox_cmd);

	atomic_set(&status, 0);

	do {
		schedule_timeout_uninterruptible(1);
	} while ((!atomic_read(&status)) && (count++ < 100000));

	ret = atomic_read(&status);
	if (!ret) {
		dev_err(&oct->pci_dev->dev, "octeon_pfvf_handshake timeout\n");
		return 1;
	}

	for (q_no = 0 ; q_no < oct->num_iqs ; q_no++)
		oct->instr_queue[q_no]->txpciq.s.pkind = oct->pfvf_hsword.pkind;

	vfmajor = LIQUIDIO_BASE_MAJOR_VERSION;
	pfmajor = ret >> 16;
	if (pfmajor != vfmajor) {
		dev_err(&oct->pci_dev->dev,
			"VF Liquidio driver (major version %d) is not compatible with Liquidio PF driver (major version %d)\n",
			vfmajor, pfmajor);
		return 1;
	}

	dev_dbg(&oct->pci_dev->dev,
		"VF Liquidio driver (major version %d), Liquidio PF driver (major version %d)\n",
		vfmajor, pfmajor);

	dev_dbg(&oct->pci_dev->dev, "got data from pf pkind is %d\n",
		oct->pfvf_hsword.pkind);

	return 0;
}