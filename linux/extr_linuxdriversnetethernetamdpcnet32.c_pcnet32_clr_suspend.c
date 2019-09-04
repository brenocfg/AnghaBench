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
typedef  int /*<<< orphan*/  ulong ;
struct pcnet32_private {TYPE_1__* a; } ;
struct TYPE_2__ {int (* read_csr ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* write_csr ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CSR5 ; 
 int CSR5_SUSPEND ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void pcnet32_clr_suspend(struct pcnet32_private *lp, ulong ioaddr)
{
	int csr5 = lp->a->read_csr(ioaddr, CSR5);
	/* clear SUSPEND (SPND) - CSR5 bit 0 */
	lp->a->write_csr(ioaddr, CSR5, csr5 & ~CSR5_SUSPEND);
}