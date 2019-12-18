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
struct cxgbi_tag_format {int dummy; } ;
struct TYPE_2__ {scalar_t__ pgsz_idx_dflt; } ;
struct cxgbi_ppm {int ppmax; TYPE_1__ tformat; } ;
struct cxgbi_device {int /*<<< orphan*/  flags; int /*<<< orphan*/  lldev; int /*<<< orphan*/  pdev; int /*<<< orphan*/ * ports; } ;

/* Variables and functions */
 int /*<<< orphan*/  CXGBI_FLAG_DDP_OFF ; 
 scalar_t__ DDP_PGIDX_MAX ; 
 int cxgbi_ppm_init (void**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cxgbi_tag_format*,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int) ; 

int cxgbi_ddp_ppm_setup(void **ppm_pp, struct cxgbi_device *cdev,
			struct cxgbi_tag_format *tformat,
			unsigned int iscsi_size, unsigned int llimit,
			unsigned int start, unsigned int rsvd_factor,
			unsigned int edram_start, unsigned int edram_size)
{
	int err = cxgbi_ppm_init(ppm_pp, cdev->ports[0], cdev->pdev,
				cdev->lldev, tformat, iscsi_size, llimit, start,
				rsvd_factor, edram_start, edram_size);

	if (err >= 0) {
		struct cxgbi_ppm *ppm = (struct cxgbi_ppm *)(*ppm_pp);

		if (ppm->ppmax < 1024 ||
		    ppm->tformat.pgsz_idx_dflt >= DDP_PGIDX_MAX)
			cdev->flags |= CXGBI_FLAG_DDP_OFF;
		err = 0;
	} else {
		cdev->flags |= CXGBI_FLAG_DDP_OFF;
	}

	return err;
}