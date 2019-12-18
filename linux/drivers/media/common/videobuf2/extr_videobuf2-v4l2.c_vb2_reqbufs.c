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
struct vb2_queue {int dummy; } ;
struct v4l2_requestbuffers {int /*<<< orphan*/  count; int /*<<< orphan*/  memory; int /*<<< orphan*/  capabilities; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  fill_buf_caps (struct vb2_queue*,int /*<<< orphan*/ *) ; 
 int vb2_core_reqbufs (struct vb2_queue*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int vb2_verify_memory_type (struct vb2_queue*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int vb2_reqbufs(struct vb2_queue *q, struct v4l2_requestbuffers *req)
{
	int ret = vb2_verify_memory_type(q, req->memory, req->type);

	fill_buf_caps(q, &req->capabilities);
	return ret ? ret : vb2_core_reqbufs(q, req->memory, &req->count);
}