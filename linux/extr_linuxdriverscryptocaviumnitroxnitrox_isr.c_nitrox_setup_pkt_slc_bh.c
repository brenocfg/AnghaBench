#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct TYPE_2__ {struct bh_data* slc; } ;
struct nitrox_device {int nr_queues; int /*<<< orphan*/ * pkt_cmdqs; TYPE_1__ bh; } ;
struct bh_data {int /*<<< orphan*/  resp_handler; int /*<<< orphan*/ * cmdq; int /*<<< orphan*/  completion_cnt_csr_addr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NITROX_CSR_ADDR (struct nitrox_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NPS_PKT_SLC_CNTSX (int) ; 
 struct bh_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pkt_slc_resp_handler ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int nitrox_setup_pkt_slc_bh(struct nitrox_device *ndev)
{
	u32 size;
	int i;

	size = ndev->nr_queues * sizeof(struct bh_data);
	ndev->bh.slc = kzalloc(size, GFP_KERNEL);
	if (!ndev->bh.slc)
		return -ENOMEM;

	for (i = 0; i < ndev->nr_queues; i++) {
		struct bh_data *bh = &ndev->bh.slc[i];
		u64 offset;

		offset = NPS_PKT_SLC_CNTSX(i);
		/* pre calculate completion count address */
		bh->completion_cnt_csr_addr = NITROX_CSR_ADDR(ndev, offset);
		bh->cmdq = &ndev->pkt_cmdqs[i];

		tasklet_init(&bh->resp_handler, pkt_slc_resp_handler,
			     (unsigned long)bh);
	}

	return 0;
}