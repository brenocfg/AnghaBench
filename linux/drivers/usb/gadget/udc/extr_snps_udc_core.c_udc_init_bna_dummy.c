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
struct udc_request {TYPE_1__* td_data; int /*<<< orphan*/  td_phys; } ;
struct TYPE_2__ {int /*<<< orphan*/  status; int /*<<< orphan*/  next; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMD_ADDBITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AMD_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UDC_DMA_IN_STS_L ; 
 int /*<<< orphan*/  UDC_DMA_STP_STS_BS ; 
 int /*<<< orphan*/  UDC_DMA_STP_STS_BS_DMA_DONE ; 
 int /*<<< orphan*/  pr_debug (char*,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void udc_init_bna_dummy(struct udc_request *req)
{
	if (req) {
		/* set last bit */
		req->td_data->status |= AMD_BIT(UDC_DMA_IN_STS_L);
		/* set next pointer to itself */
		req->td_data->next = req->td_phys;
		/* set HOST BUSY */
		req->td_data->status
			= AMD_ADDBITS(req->td_data->status,
					UDC_DMA_STP_STS_BS_DMA_DONE,
					UDC_DMA_STP_STS_BS);
#ifdef UDC_VERBOSE
		pr_debug("bna desc = %p, sts = %08x\n",
			req->td_data, req->td_data->status);
#endif
	}
}