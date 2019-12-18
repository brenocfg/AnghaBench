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
struct e1000_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_BPRC ; 
 int /*<<< orphan*/  E1000_BPTC ; 
 int /*<<< orphan*/  E1000_COLC ; 
 int /*<<< orphan*/  E1000_CRCERRS ; 
 int /*<<< orphan*/  E1000_DC ; 
 int /*<<< orphan*/  E1000_ECOL ; 
 int /*<<< orphan*/  E1000_FCRUC ; 
 int /*<<< orphan*/  E1000_GORCH ; 
 int /*<<< orphan*/  E1000_GORCL ; 
 int /*<<< orphan*/  E1000_GOTCH ; 
 int /*<<< orphan*/  E1000_GOTCL ; 
 int /*<<< orphan*/  E1000_GPRC ; 
 int /*<<< orphan*/  E1000_GPTC ; 
 int /*<<< orphan*/  E1000_LATECOL ; 
 int /*<<< orphan*/  E1000_MCC ; 
 int /*<<< orphan*/  E1000_MPC ; 
 int /*<<< orphan*/  E1000_MPRC ; 
 int /*<<< orphan*/  E1000_MPTC ; 
 int /*<<< orphan*/  E1000_RFC ; 
 int /*<<< orphan*/  E1000_RJC ; 
 int /*<<< orphan*/  E1000_RLEC ; 
 int /*<<< orphan*/  E1000_RNBC ; 
 int /*<<< orphan*/  E1000_ROC ; 
 int /*<<< orphan*/  E1000_RUC ; 
 int /*<<< orphan*/  E1000_SCC ; 
 int /*<<< orphan*/  E1000_SEC ; 
 int /*<<< orphan*/  E1000_SYMERRS ; 
 int /*<<< orphan*/  E1000_TORH ; 
 int /*<<< orphan*/  E1000_TORL ; 
 int /*<<< orphan*/  E1000_TOTH ; 
 int /*<<< orphan*/  E1000_TOTL ; 
 int /*<<< orphan*/  E1000_TPR ; 
 int /*<<< orphan*/  E1000_TPT ; 
 int /*<<< orphan*/  E1000_XOFFRXC ; 
 int /*<<< orphan*/  E1000_XOFFTXC ; 
 int /*<<< orphan*/  E1000_XONRXC ; 
 int /*<<< orphan*/  E1000_XONTXC ; 
 int /*<<< orphan*/  rd32 (int /*<<< orphan*/ ) ; 

void igb_clear_hw_cntrs_base(struct e1000_hw *hw)
{
	rd32(E1000_CRCERRS);
	rd32(E1000_SYMERRS);
	rd32(E1000_MPC);
	rd32(E1000_SCC);
	rd32(E1000_ECOL);
	rd32(E1000_MCC);
	rd32(E1000_LATECOL);
	rd32(E1000_COLC);
	rd32(E1000_DC);
	rd32(E1000_SEC);
	rd32(E1000_RLEC);
	rd32(E1000_XONRXC);
	rd32(E1000_XONTXC);
	rd32(E1000_XOFFRXC);
	rd32(E1000_XOFFTXC);
	rd32(E1000_FCRUC);
	rd32(E1000_GPRC);
	rd32(E1000_BPRC);
	rd32(E1000_MPRC);
	rd32(E1000_GPTC);
	rd32(E1000_GORCL);
	rd32(E1000_GORCH);
	rd32(E1000_GOTCL);
	rd32(E1000_GOTCH);
	rd32(E1000_RNBC);
	rd32(E1000_RUC);
	rd32(E1000_RFC);
	rd32(E1000_ROC);
	rd32(E1000_RJC);
	rd32(E1000_TORL);
	rd32(E1000_TORH);
	rd32(E1000_TOTL);
	rd32(E1000_TOTH);
	rd32(E1000_TPR);
	rd32(E1000_TPT);
	rd32(E1000_MPTC);
	rd32(E1000_BPTC);
}