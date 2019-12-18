#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* parent; } ;
struct platform_device {TYPE_2__ dev; } ;
struct fastrpc_session_ctx {scalar_t__ sid; } ;
struct fastrpc_channel_ctx {int /*<<< orphan*/  lock; int /*<<< orphan*/  sesscount; TYPE_1__* session; } ;
struct TYPE_3__ {scalar_t__ sid; int valid; } ;

/* Variables and functions */
 int FASTRPC_MAX_SESSIONS ; 
 void* dev_get_drvdata (TYPE_2__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int fastrpc_cb_remove(struct platform_device *pdev)
{
	struct fastrpc_channel_ctx *cctx = dev_get_drvdata(pdev->dev.parent);
	struct fastrpc_session_ctx *sess = dev_get_drvdata(&pdev->dev);
	unsigned long flags;
	int i;

	spin_lock_irqsave(&cctx->lock, flags);
	for (i = 1; i < FASTRPC_MAX_SESSIONS; i++) {
		if (cctx->session[i].sid == sess->sid) {
			cctx->session[i].valid = false;
			cctx->sesscount--;
		}
	}
	spin_unlock_irqrestore(&cctx->lock, flags);

	return 0;
}