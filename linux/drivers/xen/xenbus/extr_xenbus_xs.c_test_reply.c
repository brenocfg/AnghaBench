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
struct xb_req_data {scalar_t__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  barrier () ; 
 scalar_t__ xb_req_state_got_reply ; 
 int /*<<< orphan*/  xenbus_ok () ; 

__attribute__((used)) static bool test_reply(struct xb_req_data *req)
{
	if (req->state == xb_req_state_got_reply || !xenbus_ok())
		return true;

	/* Make sure to reread req->state each time. */
	barrier();

	return false;
}