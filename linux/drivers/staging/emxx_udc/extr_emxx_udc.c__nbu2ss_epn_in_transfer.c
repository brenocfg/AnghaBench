#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct nbu2ss_udc {TYPE_2__* p_regs; } ;
struct TYPE_6__ {scalar_t__ actual; size_t length; } ;
struct nbu2ss_req {TYPE_3__ req; } ;
struct nbu2ss_ep {scalar_t__ epnum; } ;
struct TYPE_5__ {TYPE_1__* EP_REGS; } ;
struct TYPE_4__ {int /*<<< orphan*/  EP_STATUS; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t EPN_IN_EMPTY ; 
 size_t EPN_IN_FULL ; 
 int _nbu2ss_epn_in_data (struct nbu2ss_udc*,struct nbu2ss_ep*,struct nbu2ss_req*,size_t) ; 
 size_t _nbu2ss_readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _nbu2ss_zero_len_pkt (struct nbu2ss_udc*,size_t) ; 

__attribute__((used)) static int _nbu2ss_epn_in_transfer(struct nbu2ss_udc *udc,
				   struct nbu2ss_ep *ep, struct nbu2ss_req *req)
{
	u32		num;
	u32		i_buf_size;
	int		result = 0;
	u32		status;

	if (ep->epnum == 0)
		return -EINVAL;

	num = ep->epnum - 1;

	status = _nbu2ss_readl(&udc->p_regs->EP_REGS[num].EP_STATUS);

	/*-------------------------------------------------------------*/
	/* State confirmation of FIFO */
	if (req->req.actual == 0) {
		if ((status & EPN_IN_EMPTY) == 0)
			return 1;	/* Not Empty */

	} else {
		if ((status & EPN_IN_FULL) != 0)
			return 1;	/* Not Empty */
	}

	/*-------------------------------------------------------------*/
	/* Start transfer */
	i_buf_size = req->req.length - req->req.actual;
	if (i_buf_size > 0)
		result = _nbu2ss_epn_in_data(udc, ep, req, i_buf_size);
	else if (req->req.length == 0)
		_nbu2ss_zero_len_pkt(udc, ep->epnum);

	return result;
}