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
struct sockaddr {int dummy; } ;
struct resolve_cb_context {int status; int /*<<< orphan*/  comp; } ;
struct rdma_dev_addr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void resolve_cb(int status, struct sockaddr *src_addr,
	     struct rdma_dev_addr *addr, void *context)
{
	((struct resolve_cb_context *)context)->status = status;
	complete(&((struct resolve_cb_context *)context)->comp);
}