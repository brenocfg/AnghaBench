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
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ length; scalar_t__ actual; } ;
struct net2280_request {TYPE_1__ req; } ;
struct net2280_ep {int dummy; } ;

/* Variables and functions */
 int DMA_BYTE_COUNT_MASK ; 
 int /*<<< orphan*/  done (struct net2280_ep*,struct net2280_request*,int) ; 

__attribute__((used)) static inline void
dma_done(struct net2280_ep *ep,	struct net2280_request *req, u32 dmacount,
		int status)
{
	req->req.actual = req->req.length - (DMA_BYTE_COUNT_MASK & dmacount);
	done(ep, req, status);
}