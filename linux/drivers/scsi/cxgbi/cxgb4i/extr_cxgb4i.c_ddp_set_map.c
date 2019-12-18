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
struct scatterlist {int dummy; } ;
struct cxgbi_task_tag_info {unsigned int idx; unsigned int npods; int /*<<< orphan*/  cid; struct scatterlist* sgl; } ;
struct cxgbi_sock {int /*<<< orphan*/  port_id; } ;
struct cxgbi_ppm {int dummy; } ;

/* Variables and functions */
 unsigned int ULPMEM_IDATA_MAX_NPPODS ; 
 int ddp_ppod_write_idata (struct cxgbi_ppm*,struct cxgbi_sock*,struct cxgbi_task_tag_info*,unsigned int,unsigned int,struct scatterlist**,unsigned int*) ; 

__attribute__((used)) static int ddp_set_map(struct cxgbi_ppm *ppm, struct cxgbi_sock *csk,
		       struct cxgbi_task_tag_info *ttinfo)
{
	unsigned int pidx = ttinfo->idx;
	unsigned int npods = ttinfo->npods;
	unsigned int i, cnt;
	int err = 0;
	struct scatterlist *sg = ttinfo->sgl;
	unsigned int offset = 0;

	ttinfo->cid = csk->port_id;

	for (i = 0; i < npods; i += cnt, pidx += cnt) {
		cnt = npods - i;

		if (cnt > ULPMEM_IDATA_MAX_NPPODS)
			cnt = ULPMEM_IDATA_MAX_NPPODS;
		err = ddp_ppod_write_idata(ppm, csk, ttinfo, pidx, cnt,
					   &sg, &offset);
		if (err < 0)
			break;
	}

	return err;
}