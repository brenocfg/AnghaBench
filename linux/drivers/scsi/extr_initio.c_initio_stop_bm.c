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
struct initio_host {scalar_t__ addr; } ;

/* Variables and functions */
 int TAX_X_ABT ; 
 int TAX_X_CLR_FIFO ; 
 int TSC_FLUSH_FIFO ; 
 scalar_t__ TUL_Int ; 
 scalar_t__ TUL_SCtrl0 ; 
 scalar_t__ TUL_XCmd ; 
 scalar_t__ TUL_XStatus ; 
 int XABT ; 
 int XPEND ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static void initio_stop_bm(struct initio_host * host)
{

	if (inb(host->addr + TUL_XStatus) & XPEND) {	/* if DMA xfer is pending, abort DMA xfer */
		outb(TAX_X_ABT | TAX_X_CLR_FIFO, host->addr + TUL_XCmd);
		/* wait Abort DMA xfer done */
		while ((inb(host->addr + TUL_Int) & XABT) == 0)
			cpu_relax();
	}
	outb(TSC_FLUSH_FIFO, host->addr + TUL_SCtrl0);
}