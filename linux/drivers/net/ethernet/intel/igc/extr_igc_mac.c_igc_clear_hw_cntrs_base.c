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
struct igc_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IGC_ALGNERRC ; 
 int /*<<< orphan*/  IGC_BPRC ; 
 int /*<<< orphan*/  IGC_BPTC ; 
 int /*<<< orphan*/  IGC_CBRMPC ; 
 int /*<<< orphan*/  IGC_CBTMPC ; 
 int /*<<< orphan*/  IGC_CEXTERR ; 
 int /*<<< orphan*/  IGC_COLC ; 
 int /*<<< orphan*/  IGC_CRCERRS ; 
 int /*<<< orphan*/  IGC_DC ; 
 int /*<<< orphan*/  IGC_ECOL ; 
 int /*<<< orphan*/  IGC_FCRUC ; 
 int /*<<< orphan*/  IGC_GORCH ; 
 int /*<<< orphan*/  IGC_GORCL ; 
 int /*<<< orphan*/  IGC_GOTCH ; 
 int /*<<< orphan*/  IGC_GOTCL ; 
 int /*<<< orphan*/  IGC_GPRC ; 
 int /*<<< orphan*/  IGC_GPTC ; 
 int /*<<< orphan*/  IGC_HGORCH ; 
 int /*<<< orphan*/  IGC_HGORCL ; 
 int /*<<< orphan*/  IGC_HGOTCH ; 
 int /*<<< orphan*/  IGC_HGOTCL ; 
 int /*<<< orphan*/  IGC_HGPTC ; 
 int /*<<< orphan*/  IGC_HTCBDPC ; 
 int /*<<< orphan*/  IGC_HTDPMC ; 
 int /*<<< orphan*/  IGC_IAC ; 
 int /*<<< orphan*/  IGC_ICRXATC ; 
 int /*<<< orphan*/  IGC_ICRXDMTC ; 
 int /*<<< orphan*/  IGC_ICRXOC ; 
 int /*<<< orphan*/  IGC_ICRXPTC ; 
 int /*<<< orphan*/  IGC_ICTXATC ; 
 int /*<<< orphan*/  IGC_ICTXPTC ; 
 int /*<<< orphan*/  IGC_ICTXQEC ; 
 int /*<<< orphan*/  IGC_ICTXQMTC ; 
 int /*<<< orphan*/  IGC_LATECOL ; 
 int /*<<< orphan*/  IGC_LENERRS ; 
 int /*<<< orphan*/  IGC_MCC ; 
 int /*<<< orphan*/  IGC_MGTPDC ; 
 int /*<<< orphan*/  IGC_MGTPRC ; 
 int /*<<< orphan*/  IGC_MGTPTC ; 
 int /*<<< orphan*/  IGC_MPC ; 
 int /*<<< orphan*/  IGC_MPRC ; 
 int /*<<< orphan*/  IGC_MPTC ; 
 int /*<<< orphan*/  IGC_PRC1023 ; 
 int /*<<< orphan*/  IGC_PRC127 ; 
 int /*<<< orphan*/  IGC_PRC1522 ; 
 int /*<<< orphan*/  IGC_PRC255 ; 
 int /*<<< orphan*/  IGC_PRC511 ; 
 int /*<<< orphan*/  IGC_PRC64 ; 
 int /*<<< orphan*/  IGC_PTC1023 ; 
 int /*<<< orphan*/  IGC_PTC127 ; 
 int /*<<< orphan*/  IGC_PTC1522 ; 
 int /*<<< orphan*/  IGC_PTC255 ; 
 int /*<<< orphan*/  IGC_PTC511 ; 
 int /*<<< orphan*/  IGC_PTC64 ; 
 int /*<<< orphan*/  IGC_RFC ; 
 int /*<<< orphan*/  IGC_RJC ; 
 int /*<<< orphan*/  IGC_RLEC ; 
 int /*<<< orphan*/  IGC_RNBC ; 
 int /*<<< orphan*/  IGC_ROC ; 
 int /*<<< orphan*/  IGC_RPTHC ; 
 int /*<<< orphan*/  IGC_RUC ; 
 int /*<<< orphan*/  IGC_RXERRC ; 
 int /*<<< orphan*/  IGC_SCC ; 
 int /*<<< orphan*/  IGC_SEC ; 
 int /*<<< orphan*/  IGC_SYMERRS ; 
 int /*<<< orphan*/  IGC_TNCRS ; 
 int /*<<< orphan*/  IGC_TORH ; 
 int /*<<< orphan*/  IGC_TORL ; 
 int /*<<< orphan*/  IGC_TOTH ; 
 int /*<<< orphan*/  IGC_TOTL ; 
 int /*<<< orphan*/  IGC_TPR ; 
 int /*<<< orphan*/  IGC_TPT ; 
 int /*<<< orphan*/  IGC_TSCTC ; 
 int /*<<< orphan*/  IGC_TSCTFC ; 
 int /*<<< orphan*/  IGC_XOFFRXC ; 
 int /*<<< orphan*/  IGC_XOFFTXC ; 
 int /*<<< orphan*/  IGC_XONRXC ; 
 int /*<<< orphan*/  IGC_XONTXC ; 
 int /*<<< orphan*/  rd32 (int /*<<< orphan*/ ) ; 

void igc_clear_hw_cntrs_base(struct igc_hw *hw)
{
	rd32(IGC_CRCERRS);
	rd32(IGC_SYMERRS);
	rd32(IGC_MPC);
	rd32(IGC_SCC);
	rd32(IGC_ECOL);
	rd32(IGC_MCC);
	rd32(IGC_LATECOL);
	rd32(IGC_COLC);
	rd32(IGC_DC);
	rd32(IGC_SEC);
	rd32(IGC_RLEC);
	rd32(IGC_XONRXC);
	rd32(IGC_XONTXC);
	rd32(IGC_XOFFRXC);
	rd32(IGC_XOFFTXC);
	rd32(IGC_FCRUC);
	rd32(IGC_GPRC);
	rd32(IGC_BPRC);
	rd32(IGC_MPRC);
	rd32(IGC_GPTC);
	rd32(IGC_GORCL);
	rd32(IGC_GORCH);
	rd32(IGC_GOTCL);
	rd32(IGC_GOTCH);
	rd32(IGC_RNBC);
	rd32(IGC_RUC);
	rd32(IGC_RFC);
	rd32(IGC_ROC);
	rd32(IGC_RJC);
	rd32(IGC_TORL);
	rd32(IGC_TORH);
	rd32(IGC_TOTL);
	rd32(IGC_TOTH);
	rd32(IGC_TPR);
	rd32(IGC_TPT);
	rd32(IGC_MPTC);
	rd32(IGC_BPTC);

	rd32(IGC_PRC64);
	rd32(IGC_PRC127);
	rd32(IGC_PRC255);
	rd32(IGC_PRC511);
	rd32(IGC_PRC1023);
	rd32(IGC_PRC1522);
	rd32(IGC_PTC64);
	rd32(IGC_PTC127);
	rd32(IGC_PTC255);
	rd32(IGC_PTC511);
	rd32(IGC_PTC1023);
	rd32(IGC_PTC1522);

	rd32(IGC_ALGNERRC);
	rd32(IGC_RXERRC);
	rd32(IGC_TNCRS);
	rd32(IGC_CEXTERR);
	rd32(IGC_TSCTC);
	rd32(IGC_TSCTFC);

	rd32(IGC_MGTPRC);
	rd32(IGC_MGTPDC);
	rd32(IGC_MGTPTC);

	rd32(IGC_IAC);
	rd32(IGC_ICRXOC);

	rd32(IGC_ICRXPTC);
	rd32(IGC_ICRXATC);
	rd32(IGC_ICTXPTC);
	rd32(IGC_ICTXATC);
	rd32(IGC_ICTXQEC);
	rd32(IGC_ICTXQMTC);
	rd32(IGC_ICRXDMTC);

	rd32(IGC_CBTMPC);
	rd32(IGC_HTDPMC);
	rd32(IGC_CBRMPC);
	rd32(IGC_RPTHC);
	rd32(IGC_HGPTC);
	rd32(IGC_HTCBDPC);
	rd32(IGC_HGORCL);
	rd32(IGC_HGORCH);
	rd32(IGC_HGOTCL);
	rd32(IGC_HGOTCH);
	rd32(IGC_LENERRS);
}