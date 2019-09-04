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
struct rbd_client_id {scalar_t__ gid; scalar_t__ handle; } ;

/* Variables and functions */

__attribute__((used)) static bool rbd_cid_equal(const struct rbd_client_id *lhs,
			  const struct rbd_client_id *rhs)
{
	return lhs->gid == rhs->gid && lhs->handle == rhs->handle;
}