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
struct controlvm_message {int dummy; } ;
struct parahotplug_request {struct controlvm_message msg; int /*<<< orphan*/  expiration; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct parahotplug_request* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parahotplug_next_expiration () ; 
 int /*<<< orphan*/  parahotplug_next_id () ; 

__attribute__((used)) static struct parahotplug_request *parahotplug_request_create(
						struct controlvm_message *msg)
{
	struct parahotplug_request *req;

	req = kmalloc(sizeof(*req), GFP_KERNEL);
	if (!req)
		return NULL;
	req->id = parahotplug_next_id();
	req->expiration = parahotplug_next_expiration();
	req->msg = *msg;
	return req;
}