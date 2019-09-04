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
struct crypto_wait {int err; int /*<<< orphan*/  completion; } ;
struct crypto_async_request {struct crypto_wait* data; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

void crypto_req_done(struct crypto_async_request *req, int err)
{
	struct crypto_wait *wait = req->data;

	if (err == -EINPROGRESS)
		return;

	wait->err = err;
	complete(&wait->completion);
}