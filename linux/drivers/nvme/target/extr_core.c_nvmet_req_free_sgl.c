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
struct nvmet_req {scalar_t__ sg_cnt; int /*<<< orphan*/ * sg; scalar_t__ p2p_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_p2pmem_free_sgl (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sgl_free (int /*<<< orphan*/ *) ; 

void nvmet_req_free_sgl(struct nvmet_req *req)
{
	if (req->p2p_dev)
		pci_p2pmem_free_sgl(req->p2p_dev, req->sg);
	else
		sgl_free(req->sg);

	req->sg = NULL;
	req->sg_cnt = 0;
}