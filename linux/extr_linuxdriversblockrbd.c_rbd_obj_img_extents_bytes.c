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
typedef  int /*<<< orphan*/  u64 ;
struct rbd_obj_request {int /*<<< orphan*/  num_img_extents; int /*<<< orphan*/  img_extents; } ;

/* Variables and functions */
 int /*<<< orphan*/  ceph_file_extents_bytes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 rbd_obj_img_extents_bytes(struct rbd_obj_request *obj_req)
{
	return ceph_file_extents_bytes(obj_req->img_extents,
				       obj_req->num_img_extents);
}