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
struct xen_blkif_ring {int dummy; } ;
struct pending_req {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  id; } ;
struct TYPE_4__ {TYPE_1__ other; } ;
struct blkif_request {int /*<<< orphan*/  operation; TYPE_2__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLKIF_RSP_EOPNOTSUPP ; 
 int EIO ; 
 int /*<<< orphan*/  free_req (struct xen_blkif_ring*,struct pending_req*) ; 
 int /*<<< orphan*/  make_response (struct xen_blkif_ring*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dispatch_other_io(struct xen_blkif_ring *ring,
			     struct blkif_request *req,
			     struct pending_req *pending_req)
{
	free_req(ring, pending_req);
	make_response(ring, req->u.other.id, req->operation,
		      BLKIF_RSP_EOPNOTSUPP);
	return -EIO;
}