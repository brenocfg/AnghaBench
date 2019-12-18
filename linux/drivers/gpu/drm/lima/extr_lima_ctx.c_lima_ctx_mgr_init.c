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
struct lima_ctx_mgr {int /*<<< orphan*/  handles; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  XA_FLAGS_ALLOC ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xa_init_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void lima_ctx_mgr_init(struct lima_ctx_mgr *mgr)
{
	mutex_init(&mgr->lock);
	xa_init_flags(&mgr->handles, XA_FLAGS_ALLOC);
}