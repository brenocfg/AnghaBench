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
struct zfcp_qdio_req {int dummy; } ;
struct zfcp_qdio {int dummy; } ;
struct scatterlist {int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int /*<<< orphan*/  sg_virt (struct scatterlist*) ; 
 int /*<<< orphan*/  zfcp_qdio_fill_next (struct zfcp_qdio*,struct zfcp_qdio_req*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_qdio_set_sbale_last (struct zfcp_qdio*,struct zfcp_qdio_req*) ; 

__attribute__((used)) static void zfcp_fsf_setup_ct_els_unchained(struct zfcp_qdio *qdio,
					    struct zfcp_qdio_req *q_req,
					    struct scatterlist *sg_req,
					    struct scatterlist *sg_resp)
{
	zfcp_qdio_fill_next(qdio, q_req, sg_virt(sg_req), sg_req->length);
	zfcp_qdio_fill_next(qdio, q_req, sg_virt(sg_resp), sg_resp->length);
	zfcp_qdio_set_sbale_last(qdio, q_req);
}