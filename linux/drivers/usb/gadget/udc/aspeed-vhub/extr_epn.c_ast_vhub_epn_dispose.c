#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct usb_ep {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/ * descs; } ;
struct TYPE_6__ {int /*<<< orphan*/ * name; int /*<<< orphan*/  ep_list; } ;
struct ast_vhub_ep {int d_idx; TYPE_5__* dev; TYPE_4__ epn; int /*<<< orphan*/ * buf; int /*<<< orphan*/  buf_dma; TYPE_3__* vhub; TYPE_1__ ep; } ;
struct TYPE_10__ {int /*<<< orphan*/ ** epns; } ;
struct TYPE_8__ {TYPE_2__* pdev; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int AST_VHUB_DESCS_COUNT ; 
 scalar_t__ AST_VHUB_EPn_MAX_PACKET ; 
 int /*<<< orphan*/  EPDBG (struct ast_vhub_ep*,char*) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 struct ast_vhub_ep* to_ast_ep (struct usb_ep*) ; 

__attribute__((used)) static void ast_vhub_epn_dispose(struct usb_ep *u_ep)
{
	struct ast_vhub_ep *ep = to_ast_ep(u_ep);

	if (WARN_ON(!ep->dev || !ep->d_idx))
		return;

	EPDBG(ep, "Releasing endpoint\n");

	/* Take it out of the EP list */
	list_del_init(&ep->ep.ep_list);

	/* Mark the address free in the device */
	ep->dev->epns[ep->d_idx - 1] = NULL;

	/* Free name & DMA buffers */
	kfree(ep->ep.name);
	ep->ep.name = NULL;
	dma_free_coherent(&ep->vhub->pdev->dev,
			  AST_VHUB_EPn_MAX_PACKET +
			  8 * AST_VHUB_DESCS_COUNT,
			  ep->buf, ep->buf_dma);
	ep->buf = NULL;
	ep->epn.descs = NULL;

	/* Mark free */
	ep->dev = NULL;
}