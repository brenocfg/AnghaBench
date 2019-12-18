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
struct fastrpc_session_ctx {int used; scalar_t__ valid; } ;
struct fastrpc_channel_ctx {int sesscount; int /*<<< orphan*/  lock; struct fastrpc_session_ctx* session; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct fastrpc_session_ctx *fastrpc_session_alloc(
					struct fastrpc_channel_ctx *cctx)
{
	struct fastrpc_session_ctx *session = NULL;
	unsigned long flags;
	int i;

	spin_lock_irqsave(&cctx->lock, flags);
	for (i = 0; i < cctx->sesscount; i++) {
		if (!cctx->session[i].used && cctx->session[i].valid) {
			cctx->session[i].used = true;
			session = &cctx->session[i];
			break;
		}
	}
	spin_unlock_irqrestore(&cctx->lock, flags);

	return session;
}