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
struct fastrpc_session_ctx {int used; } ;
struct fastrpc_channel_ctx {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void fastrpc_session_free(struct fastrpc_channel_ctx *cctx,
				 struct fastrpc_session_ctx *session)
{
	unsigned long flags;

	spin_lock_irqsave(&cctx->lock, flags);
	session->used = false;
	spin_unlock_irqrestore(&cctx->lock, flags);
}