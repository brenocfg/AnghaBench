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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct qib_ctxtdata {int /*<<< orphan*/  ctxt; int /*<<< orphan*/  dd; } ;

/* Variables and functions */
 int /*<<< orphan*/  mmiowb () ; 
 int /*<<< orphan*/  qib_write_ureg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ur_rcvegrindexhead ; 
 int /*<<< orphan*/  ur_rcvhdrhead ; 

__attribute__((used)) static void qib_update_6120_usrhead(struct qib_ctxtdata *rcd, u64 hd,
				    u32 updegr, u32 egrhd, u32 npkts)
{
	if (updegr)
		qib_write_ureg(rcd->dd, ur_rcvegrindexhead, egrhd, rcd->ctxt);
	mmiowb();
	qib_write_ureg(rcd->dd, ur_rcvhdrhead, hd, rcd->ctxt);
	mmiowb();
}