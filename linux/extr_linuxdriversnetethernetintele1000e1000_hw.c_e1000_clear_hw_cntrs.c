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
typedef  int /*<<< orphan*/  u32 ;
struct e1000_hw {scalar_t__ mac_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALGNERRC ; 
 int /*<<< orphan*/  BPRC ; 
 int /*<<< orphan*/  BPTC ; 
 int /*<<< orphan*/  CEXTERR ; 
 int /*<<< orphan*/  COLC ; 
 int /*<<< orphan*/  CRCERRS ; 
 int /*<<< orphan*/  DC ; 
 int /*<<< orphan*/  ECOL ; 
 int /*<<< orphan*/  FCRUC ; 
 int /*<<< orphan*/  GORCH ; 
 int /*<<< orphan*/  GORCL ; 
 int /*<<< orphan*/  GOTCH ; 
 int /*<<< orphan*/  GOTCL ; 
 int /*<<< orphan*/  GPRC ; 
 int /*<<< orphan*/  GPTC ; 
 int /*<<< orphan*/  LATECOL ; 
 int /*<<< orphan*/  MCC ; 
 int /*<<< orphan*/  MGTPDC ; 
 int /*<<< orphan*/  MGTPRC ; 
 int /*<<< orphan*/  MGTPTC ; 
 int /*<<< orphan*/  MPC ; 
 int /*<<< orphan*/  MPRC ; 
 int /*<<< orphan*/  MPTC ; 
 int /*<<< orphan*/  PRC1023 ; 
 int /*<<< orphan*/  PRC127 ; 
 int /*<<< orphan*/  PRC1522 ; 
 int /*<<< orphan*/  PRC255 ; 
 int /*<<< orphan*/  PRC511 ; 
 int /*<<< orphan*/  PRC64 ; 
 int /*<<< orphan*/  PTC1023 ; 
 int /*<<< orphan*/  PTC127 ; 
 int /*<<< orphan*/  PTC1522 ; 
 int /*<<< orphan*/  PTC255 ; 
 int /*<<< orphan*/  PTC511 ; 
 int /*<<< orphan*/  PTC64 ; 
 int /*<<< orphan*/  RFC ; 
 int /*<<< orphan*/  RJC ; 
 int /*<<< orphan*/  RLEC ; 
 int /*<<< orphan*/  RNBC ; 
 int /*<<< orphan*/  ROC ; 
 int /*<<< orphan*/  RUC ; 
 int /*<<< orphan*/  RXERRC ; 
 int /*<<< orphan*/  SCC ; 
 int /*<<< orphan*/  SEC ; 
 int /*<<< orphan*/  SYMERRS ; 
 int /*<<< orphan*/  TNCRS ; 
 int /*<<< orphan*/  TORH ; 
 int /*<<< orphan*/  TORL ; 
 int /*<<< orphan*/  TOTH ; 
 int /*<<< orphan*/  TOTL ; 
 int /*<<< orphan*/  TPR ; 
 int /*<<< orphan*/  TPT ; 
 int /*<<< orphan*/  TSCTC ; 
 int /*<<< orphan*/  TSCTFC ; 
 int /*<<< orphan*/  XOFFRXC ; 
 int /*<<< orphan*/  XOFFTXC ; 
 int /*<<< orphan*/  XONRXC ; 
 int /*<<< orphan*/  XONTXC ; 
 scalar_t__ e1000_82543 ; 
 scalar_t__ e1000_82544 ; 
 int /*<<< orphan*/  er32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void e1000_clear_hw_cntrs(struct e1000_hw *hw)
{
	volatile u32 temp;

	temp = er32(CRCERRS);
	temp = er32(SYMERRS);
	temp = er32(MPC);
	temp = er32(SCC);
	temp = er32(ECOL);
	temp = er32(MCC);
	temp = er32(LATECOL);
	temp = er32(COLC);
	temp = er32(DC);
	temp = er32(SEC);
	temp = er32(RLEC);
	temp = er32(XONRXC);
	temp = er32(XONTXC);
	temp = er32(XOFFRXC);
	temp = er32(XOFFTXC);
	temp = er32(FCRUC);

	temp = er32(PRC64);
	temp = er32(PRC127);
	temp = er32(PRC255);
	temp = er32(PRC511);
	temp = er32(PRC1023);
	temp = er32(PRC1522);

	temp = er32(GPRC);
	temp = er32(BPRC);
	temp = er32(MPRC);
	temp = er32(GPTC);
	temp = er32(GORCL);
	temp = er32(GORCH);
	temp = er32(GOTCL);
	temp = er32(GOTCH);
	temp = er32(RNBC);
	temp = er32(RUC);
	temp = er32(RFC);
	temp = er32(ROC);
	temp = er32(RJC);
	temp = er32(TORL);
	temp = er32(TORH);
	temp = er32(TOTL);
	temp = er32(TOTH);
	temp = er32(TPR);
	temp = er32(TPT);

	temp = er32(PTC64);
	temp = er32(PTC127);
	temp = er32(PTC255);
	temp = er32(PTC511);
	temp = er32(PTC1023);
	temp = er32(PTC1522);

	temp = er32(MPTC);
	temp = er32(BPTC);

	if (hw->mac_type < e1000_82543)
		return;

	temp = er32(ALGNERRC);
	temp = er32(RXERRC);
	temp = er32(TNCRS);
	temp = er32(CEXTERR);
	temp = er32(TSCTC);
	temp = er32(TSCTFC);

	if (hw->mac_type <= e1000_82544)
		return;

	temp = er32(MGTPRC);
	temp = er32(MGTPDC);
	temp = er32(MGTPTC);
}