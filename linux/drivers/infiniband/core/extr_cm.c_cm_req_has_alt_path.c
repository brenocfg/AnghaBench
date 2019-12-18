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
struct cm_req_msg {int /*<<< orphan*/  alt_local_gid; scalar_t__ alt_local_lid; } ;

/* Variables and functions */
 scalar_t__ ib_is_opa_gid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool cm_req_has_alt_path(struct cm_req_msg *req_msg)
{
	return ((req_msg->alt_local_lid) ||
		(ib_is_opa_gid(&req_msg->alt_local_gid)));
}