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
struct mv_cesa_engine {int /*<<< orphan*/  queue; } ;
struct crypto_async_request {int dummy; } ;

/* Variables and functions */
 struct crypto_async_request* crypto_dequeue_request (int /*<<< orphan*/ *) ; 
 struct crypto_async_request* crypto_get_backlog (int /*<<< orphan*/ *) ; 

struct crypto_async_request *
mv_cesa_dequeue_req_locked(struct mv_cesa_engine *engine,
			   struct crypto_async_request **backlog)
{
	struct crypto_async_request *req;

	*backlog = crypto_get_backlog(&engine->queue);
	req = crypto_dequeue_request(&engine->queue);

	if (!req)
		return NULL;

	return req;
}