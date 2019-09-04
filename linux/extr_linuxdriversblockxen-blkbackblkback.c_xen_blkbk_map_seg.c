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
struct pending_req {scalar_t__ operation; int /*<<< orphan*/  nr_segs; int /*<<< orphan*/  segments; int /*<<< orphan*/  ring; } ;

/* Variables and functions */
 scalar_t__ BLKIF_OP_READ ; 
 int xen_blkbk_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int xen_blkbk_map_seg(struct pending_req *pending_req)
{
	int rc;

	rc = xen_blkbk_map(pending_req->ring, pending_req->segments,
			   pending_req->nr_segs,
	                   (pending_req->operation != BLKIF_OP_READ));

	return rc;
}