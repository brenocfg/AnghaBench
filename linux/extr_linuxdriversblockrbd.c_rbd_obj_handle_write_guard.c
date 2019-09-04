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
struct rbd_obj_request {int /*<<< orphan*/  write_state; int /*<<< orphan*/  num_img_extents; int /*<<< orphan*/  img_extents; TYPE_1__* img_request; } ;
struct rbd_device {int /*<<< orphan*/  parent_overlap; } ;
struct TYPE_2__ {struct rbd_device* rbd_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  RBD_OBJ_WRITE_COPYUP ; 
 int /*<<< orphan*/  RBD_OBJ_WRITE_FLAT ; 
 int /*<<< orphan*/  prune_extents (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rbd_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rbd_obj_img_extents_bytes (struct rbd_obj_request*) ; 
 int rbd_obj_issue_copyup (struct rbd_obj_request*,int /*<<< orphan*/ ) ; 
 int rbd_obj_read_from_parent (struct rbd_obj_request*) ; 
 int setup_copyup_bvecs (struct rbd_obj_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rbd_obj_handle_write_guard(struct rbd_obj_request *obj_req)
{
	struct rbd_device *rbd_dev = obj_req->img_request->rbd_dev;
	int ret;

	rbd_assert(obj_req->num_img_extents);
	prune_extents(obj_req->img_extents, &obj_req->num_img_extents,
		      rbd_dev->parent_overlap);
	if (!obj_req->num_img_extents) {
		/*
		 * The overlap has become 0 (most likely because the
		 * image has been flattened).  Use rbd_obj_issue_copyup()
		 * to re-submit the original write request -- the copyup
		 * operation itself will be a no-op, since someone must
		 * have populated the child object while we weren't
		 * looking.  Move to WRITE_FLAT state as we'll be done
		 * with the operation once the null copyup completes.
		 */
		obj_req->write_state = RBD_OBJ_WRITE_FLAT;
		return rbd_obj_issue_copyup(obj_req, 0);
	}

	ret = setup_copyup_bvecs(obj_req, rbd_obj_img_extents_bytes(obj_req));
	if (ret)
		return ret;

	obj_req->write_state = RBD_OBJ_WRITE_COPYUP;
	return rbd_obj_read_from_parent(obj_req);
}