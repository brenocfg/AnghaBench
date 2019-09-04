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
struct mv_cesa_engine {int /*<<< orphan*/  complete_queue; } ;
struct crypto_async_request {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
mv_cesa_engine_enqueue_complete_request(struct mv_cesa_engine *engine,
					struct crypto_async_request *req)
{
	list_add_tail(&req->list, &engine->complete_queue);
}