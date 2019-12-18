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
struct zfcp_qdio_req {int /*<<< orphan*/  sbal_number; int /*<<< orphan*/  sbal_first; int /*<<< orphan*/  sbtype; } ;
struct zfcp_qdio {int /*<<< orphan*/  req_q; int /*<<< orphan*/  req_q_full; } ;
struct scatterlist {int /*<<< orphan*/  length; } ;
struct qdio_buffer_element {int /*<<< orphan*/  length; int /*<<< orphan*/  addr; int /*<<< orphan*/  sflags; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_virt (struct scatterlist*) ; 
 struct qdio_buffer_element* zfcp_qdio_sbale_next (struct zfcp_qdio*,struct zfcp_qdio_req*) ; 
 struct qdio_buffer_element* zfcp_qdio_sbale_req (struct zfcp_qdio*,struct zfcp_qdio_req*) ; 
 int /*<<< orphan*/  zfcp_qdio_zero_sbals (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int zfcp_qdio_sbals_from_sg(struct zfcp_qdio *qdio, struct zfcp_qdio_req *q_req,
			    struct scatterlist *sg)
{
	struct qdio_buffer_element *sbale;

	/* set storage-block type for this request */
	sbale = zfcp_qdio_sbale_req(qdio, q_req);
	sbale->sflags |= q_req->sbtype;

	for (; sg; sg = sg_next(sg)) {
		sbale = zfcp_qdio_sbale_next(qdio, q_req);
		if (!sbale) {
			atomic_inc(&qdio->req_q_full);
			zfcp_qdio_zero_sbals(qdio->req_q, q_req->sbal_first,
					     q_req->sbal_number);
			return -EINVAL;
		}
		sbale->addr = sg_virt(sg);
		sbale->length = sg->length;
	}
	return 0;
}