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
struct lance_regs {int rdp; int /*<<< orphan*/  rap; } ;
struct lance_private {struct lance_regs* ll; } ;

/* Variables and functions */
 int EIO ; 
 int LE_C0_ERR ; 
 int LE_C0_IDON ; 
 int LE_C0_INEA ; 
 int LE_C0_INIT ; 
 int LE_C0_STRT ; 
 int /*<<< orphan*/  LE_CSR0 ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  pr_err (char*,int,int) ; 

__attribute__((used)) static int init_restart_lance(struct lance_private *lp)
{
	volatile struct lance_regs *ll = lp->ll;
	int i;

	ll->rap = LE_CSR0;
	ll->rdp = LE_C0_INIT;

	/* Wait for the lance to complete initialization */
	for (i = 0; (i < 100) && !(ll->rdp & (LE_C0_ERR | LE_C0_IDON)); i++)
		barrier();
	if ((i == 100) || (ll->rdp & LE_C0_ERR)) {
		pr_err("unopened after %d ticks, csr0=%04x\n", i, ll->rdp);
		return -EIO;
	}

	/* Clear IDON by writing a "1", enable interrupts and start lance */
	ll->rdp = LE_C0_IDON;
	ll->rdp = LE_C0_INEA | LE_C0_STRT;

	return 0;
}