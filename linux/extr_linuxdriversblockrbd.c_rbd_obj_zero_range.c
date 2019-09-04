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
typedef  int /*<<< orphan*/  u32 ;
struct rbd_obj_request {int /*<<< orphan*/  bvec_pos; int /*<<< orphan*/  bio_pos; TYPE_1__* img_request; } ;
struct TYPE_2__ {int data_type; } ;

/* Variables and functions */
#define  OBJ_REQUEST_BIO 130 
#define  OBJ_REQUEST_BVECS 129 
#define  OBJ_REQUEST_OWN_BVECS 128 
 int /*<<< orphan*/  rbd_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zero_bios (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zero_bvecs (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rbd_obj_zero_range(struct rbd_obj_request *obj_req, u32 off,
			       u32 bytes)
{
	switch (obj_req->img_request->data_type) {
	case OBJ_REQUEST_BIO:
		zero_bios(&obj_req->bio_pos, off, bytes);
		break;
	case OBJ_REQUEST_BVECS:
	case OBJ_REQUEST_OWN_BVECS:
		zero_bvecs(&obj_req->bvec_pos, off, bytes);
		break;
	default:
		rbd_assert(0);
	}
}