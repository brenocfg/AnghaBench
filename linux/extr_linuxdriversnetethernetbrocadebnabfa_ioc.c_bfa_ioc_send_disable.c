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
struct bfi_ioc_ctrl_req {int /*<<< orphan*/  tv_sec; void* rsvd; void* clscode; int /*<<< orphan*/  mh; } ;
struct bfa_ioc {int /*<<< orphan*/  clscode; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFI_IOC_H2I_DISABLE_REQ ; 
 int /*<<< orphan*/  BFI_MC_IOC ; 
 int /*<<< orphan*/  bfa_ioc_mbox_send (struct bfa_ioc*,struct bfi_ioc_ctrl_req*,int) ; 
 int /*<<< orphan*/  bfa_ioc_portid (struct bfa_ioc*) ; 
 int /*<<< orphan*/  bfi_h2i_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get_real_seconds () ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_ioc_send_disable(struct bfa_ioc *ioc)
{
	struct bfi_ioc_ctrl_req disable_req;

	bfi_h2i_set(disable_req.mh, BFI_MC_IOC, BFI_IOC_H2I_DISABLE_REQ,
		    bfa_ioc_portid(ioc));
	disable_req.clscode = htons(ioc->clscode);
	disable_req.rsvd = htons(0);
	/* overflow in 2106 */
	disable_req.tv_sec = ntohl(ktime_get_real_seconds());
	bfa_ioc_mbox_send(ioc, &disable_req, sizeof(struct bfi_ioc_ctrl_req));
}