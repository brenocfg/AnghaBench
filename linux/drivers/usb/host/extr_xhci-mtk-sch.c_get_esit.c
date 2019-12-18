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
typedef  int u32 ;
struct xhci_ep_ctx {int /*<<< orphan*/  ep_info; } ;

/* Variables and functions */
 int CTX_TO_EP_INTERVAL (int /*<<< orphan*/ ) ; 
 int XHCI_MTK_MAX_ESIT ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 get_esit(struct xhci_ep_ctx *ep_ctx)
{
	u32 esit;

	esit = 1 << CTX_TO_EP_INTERVAL(le32_to_cpu(ep_ctx->ep_info));
	if (esit > XHCI_MTK_MAX_ESIT)
		esit = XHCI_MTK_MAX_ESIT;

	return esit;
}