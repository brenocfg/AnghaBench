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
typedef  int /*<<< orphan*/  u8 ;
struct hif_scatter_req {int scat_entries; TYPE_1__* scat_list; int /*<<< orphan*/ * virt_dma_buf; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath6kl_hif_cp_scat_dma_buf(struct hif_scatter_req *req,
				      bool from_dma)
{
	u8 *buf;
	int i;

	buf = req->virt_dma_buf;

	for (i = 0; i < req->scat_entries; i++) {
		if (from_dma)
			memcpy(req->scat_list[i].buf, buf,
			       req->scat_list[i].len);
		else
			memcpy(buf, req->scat_list[i].buf,
			       req->scat_list[i].len);

		buf += req->scat_list[i].len;
	}

	return 0;
}