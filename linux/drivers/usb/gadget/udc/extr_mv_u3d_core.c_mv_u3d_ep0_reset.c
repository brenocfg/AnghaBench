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
typedef  int u32 ;
struct mv_u3d_ep {int /*<<< orphan*/ * ep_context; struct mv_u3d* u3d; } ;
struct mv_u3d {TYPE_2__* vuc_regs; int /*<<< orphan*/ * ep_context; struct mv_u3d_ep* eps; } ;
struct TYPE_4__ {TYPE_1__* epcr; } ;
struct TYPE_3__ {int /*<<< orphan*/  epxincr1; int /*<<< orphan*/  epxincr0; int /*<<< orphan*/  epxoutcr1; int /*<<< orphan*/  epxoutcr0; } ;

/* Variables and functions */
 int MV_U3D_EP0_MAX_PKT_SIZE ; 
 int MV_U3D_EPXCR_EP_ENABLE_SHIFT ; 
 int MV_U3D_EPXCR_EP_INIT ; 
 int MV_U3D_EPXCR_EP_TYPE_CONTROL ; 
 int MV_U3D_EPXCR_MAX_BURST_SIZE_SHIFT ; 
 int MV_U3D_EPXCR_MAX_PACKET_SIZE_SHIFT ; 
 int ioread32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void mv_u3d_ep0_reset(struct mv_u3d *u3d)
{
	struct mv_u3d_ep *ep;
	u32 epxcr;
	int i;

	for (i = 0; i < 2; i++) {
		ep = &u3d->eps[i];
		ep->u3d = u3d;

		/* ep0 ep context, ep0 in and out share the same ep context */
		ep->ep_context = &u3d->ep_context[1];
	}

	/* reset ep state machine */
	/* reset ep0 out */
	epxcr = ioread32(&u3d->vuc_regs->epcr[0].epxoutcr0);
	epxcr |= MV_U3D_EPXCR_EP_INIT;
	iowrite32(epxcr, &u3d->vuc_regs->epcr[0].epxoutcr0);
	udelay(5);
	epxcr &= ~MV_U3D_EPXCR_EP_INIT;
	iowrite32(epxcr, &u3d->vuc_regs->epcr[0].epxoutcr0);

	epxcr = ((MV_U3D_EP0_MAX_PKT_SIZE
		<< MV_U3D_EPXCR_MAX_PACKET_SIZE_SHIFT)
		| (1 << MV_U3D_EPXCR_MAX_BURST_SIZE_SHIFT)
		| (1 << MV_U3D_EPXCR_EP_ENABLE_SHIFT)
		| MV_U3D_EPXCR_EP_TYPE_CONTROL);
	iowrite32(epxcr, &u3d->vuc_regs->epcr[0].epxoutcr1);

	/* reset ep0 in */
	epxcr = ioread32(&u3d->vuc_regs->epcr[0].epxincr0);
	epxcr |= MV_U3D_EPXCR_EP_INIT;
	iowrite32(epxcr, &u3d->vuc_regs->epcr[0].epxincr0);
	udelay(5);
	epxcr &= ~MV_U3D_EPXCR_EP_INIT;
	iowrite32(epxcr, &u3d->vuc_regs->epcr[0].epxincr0);

	epxcr = ((MV_U3D_EP0_MAX_PKT_SIZE
		<< MV_U3D_EPXCR_MAX_PACKET_SIZE_SHIFT)
		| (1 << MV_U3D_EPXCR_MAX_BURST_SIZE_SHIFT)
		| (1 << MV_U3D_EPXCR_EP_ENABLE_SHIFT)
		| MV_U3D_EPXCR_EP_TYPE_CONTROL);
	iowrite32(epxcr, &u3d->vuc_regs->epcr[0].epxincr1);
}