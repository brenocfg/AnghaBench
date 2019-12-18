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
struct media_request_object {int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  vb2_core_req_ops ; 

bool vb2_request_object_is_buffer(struct media_request_object *obj)
{
	return obj->ops == &vb2_core_req_ops;
}