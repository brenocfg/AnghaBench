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
struct xc {int no; int /*<<< orphan*/  sram_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETX_PA_XMAC (int) ; 
 int /*<<< orphan*/  NETX_PA_XPEC (int) ; 
 int /*<<< orphan*/  SRAM_INTERNAL_PHYS (int) ; 
 int /*<<< orphan*/  SRAM_MEM_SIZE ; 
 int /*<<< orphan*/  XMAC_MEM_SIZE ; 
 int /*<<< orphan*/  XPEC_MEM_SIZE ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct xc*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xc_in_use ; 
 int /*<<< orphan*/  xc_lock ; 

void free_xc(struct xc *x)
{
	int xcno = x->no;

	mutex_lock(&xc_lock);

	iounmap(x->sram_base);
	release_mem_region(SRAM_INTERNAL_PHYS(xcno), SRAM_MEM_SIZE);
	release_mem_region(NETX_PA_XMAC(xcno), XMAC_MEM_SIZE);
	release_mem_region(NETX_PA_XPEC(xcno), XPEC_MEM_SIZE);
	xc_in_use &= ~(1 << x->no);
	kfree(x);

	mutex_unlock(&xc_lock);
}