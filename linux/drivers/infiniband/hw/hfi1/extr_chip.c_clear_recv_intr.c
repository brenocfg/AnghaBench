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
typedef  scalar_t__ u32 ;
struct hfi1_devdata {int dummy; } ;
struct hfi1_ctxtdata {int ireg; int /*<<< orphan*/  imask; struct hfi1_devdata* dd; } ;

/* Variables and functions */
 scalar_t__ CCE_INT_CLEAR ; 
 int /*<<< orphan*/  read_csr (struct hfi1_devdata*,scalar_t__) ; 
 int /*<<< orphan*/  write_csr (struct hfi1_devdata*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void clear_recv_intr(struct hfi1_ctxtdata *rcd)
{
	struct hfi1_devdata *dd = rcd->dd;
	u32 addr = CCE_INT_CLEAR + (8 * rcd->ireg);

	write_csr(dd, addr, rcd->imask);
	/* force the above write on the chip and get a value back */
	(void)read_csr(dd, addr);
}