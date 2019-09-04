#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct request_sock {TYPE_1__* rsk_ops; scalar_t__ rsk_listener; } ;
struct TYPE_2__ {int /*<<< orphan*/  slab; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct request_sock*) ; 
 int /*<<< orphan*/  sock_put (scalar_t__) ; 

__attribute__((used)) static inline void chtls_reqsk_free(struct request_sock *req)
{
	if (req->rsk_listener)
		sock_put(req->rsk_listener);
	kmem_cache_free(req->rsk_ops->slab, req);
}