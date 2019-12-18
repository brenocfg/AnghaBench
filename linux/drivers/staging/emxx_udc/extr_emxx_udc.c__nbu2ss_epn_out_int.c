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
struct nbu2ss_udc {int dummy; } ;
struct nbu2ss_req {int dummy; } ;
struct nbu2ss_ep {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _nbu2ss_ep_done (struct nbu2ss_ep*,struct nbu2ss_req*,int) ; 
 int _nbu2ss_epn_out_transfer (struct nbu2ss_udc*,struct nbu2ss_ep*,struct nbu2ss_req*) ; 

__attribute__((used)) static inline void _nbu2ss_epn_out_int(struct nbu2ss_udc *udc,
				       struct nbu2ss_ep *ep,
				       struct nbu2ss_req *req)
{
	int	result;

	result = _nbu2ss_epn_out_transfer(udc, ep, req);
	if (result <= 0)
		_nbu2ss_ep_done(ep, req, result);
}