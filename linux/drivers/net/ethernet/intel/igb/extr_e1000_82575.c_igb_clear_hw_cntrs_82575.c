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
struct TYPE_2__ {scalar_t__ media_type; } ;
struct e1000_hw {TYPE_1__ phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_ALGNERRC ; 
 int /*<<< orphan*/  E1000_CBRMPC ; 
 int /*<<< orphan*/  E1000_CBTMPC ; 
 int /*<<< orphan*/  E1000_CEXTERR ; 
 int /*<<< orphan*/  E1000_HGORCH ; 
 int /*<<< orphan*/  E1000_HGORCL ; 
 int /*<<< orphan*/  E1000_HGOTCH ; 
 int /*<<< orphan*/  E1000_HGOTCL ; 
 int /*<<< orphan*/  E1000_HGPTC ; 
 int /*<<< orphan*/  E1000_HTCBDPC ; 
 int /*<<< orphan*/  E1000_HTDPMC ; 
 int /*<<< orphan*/  E1000_IAC ; 
 int /*<<< orphan*/  E1000_ICRXATC ; 
 int /*<<< orphan*/  E1000_ICRXDMTC ; 
 int /*<<< orphan*/  E1000_ICRXOC ; 
 int /*<<< orphan*/  E1000_ICRXPTC ; 
 int /*<<< orphan*/  E1000_ICTXATC ; 
 int /*<<< orphan*/  E1000_ICTXPTC ; 
 int /*<<< orphan*/  E1000_ICTXQEC ; 
 int /*<<< orphan*/  E1000_ICTXQMTC ; 
 int /*<<< orphan*/  E1000_LENERRS ; 
 int /*<<< orphan*/  E1000_MGTPDC ; 
 int /*<<< orphan*/  E1000_MGTPRC ; 
 int /*<<< orphan*/  E1000_MGTPTC ; 
 int /*<<< orphan*/  E1000_PRC1023 ; 
 int /*<<< orphan*/  E1000_PRC127 ; 
 int /*<<< orphan*/  E1000_PRC1522 ; 
 int /*<<< orphan*/  E1000_PRC255 ; 
 int /*<<< orphan*/  E1000_PRC511 ; 
 int /*<<< orphan*/  E1000_PRC64 ; 
 int /*<<< orphan*/  E1000_PTC1023 ; 
 int /*<<< orphan*/  E1000_PTC127 ; 
 int /*<<< orphan*/  E1000_PTC1522 ; 
 int /*<<< orphan*/  E1000_PTC255 ; 
 int /*<<< orphan*/  E1000_PTC511 ; 
 int /*<<< orphan*/  E1000_PTC64 ; 
 int /*<<< orphan*/  E1000_RPTHC ; 
 int /*<<< orphan*/  E1000_RXERRC ; 
 int /*<<< orphan*/  E1000_SCVPC ; 
 int /*<<< orphan*/  E1000_TNCRS ; 
 int /*<<< orphan*/  E1000_TSCTC ; 
 int /*<<< orphan*/  E1000_TSCTFC ; 
 scalar_t__ e1000_media_type_internal_serdes ; 
 int /*<<< orphan*/  igb_clear_hw_cntrs_base (struct e1000_hw*) ; 
 scalar_t__ igb_sgmii_active_82575 (struct e1000_hw*) ; 
 int /*<<< orphan*/  rd32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void igb_clear_hw_cntrs_82575(struct e1000_hw *hw)
{
	igb_clear_hw_cntrs_base(hw);

	rd32(E1000_PRC64);
	rd32(E1000_PRC127);
	rd32(E1000_PRC255);
	rd32(E1000_PRC511);
	rd32(E1000_PRC1023);
	rd32(E1000_PRC1522);
	rd32(E1000_PTC64);
	rd32(E1000_PTC127);
	rd32(E1000_PTC255);
	rd32(E1000_PTC511);
	rd32(E1000_PTC1023);
	rd32(E1000_PTC1522);

	rd32(E1000_ALGNERRC);
	rd32(E1000_RXERRC);
	rd32(E1000_TNCRS);
	rd32(E1000_CEXTERR);
	rd32(E1000_TSCTC);
	rd32(E1000_TSCTFC);

	rd32(E1000_MGTPRC);
	rd32(E1000_MGTPDC);
	rd32(E1000_MGTPTC);

	rd32(E1000_IAC);
	rd32(E1000_ICRXOC);

	rd32(E1000_ICRXPTC);
	rd32(E1000_ICRXATC);
	rd32(E1000_ICTXPTC);
	rd32(E1000_ICTXATC);
	rd32(E1000_ICTXQEC);
	rd32(E1000_ICTXQMTC);
	rd32(E1000_ICRXDMTC);

	rd32(E1000_CBTMPC);
	rd32(E1000_HTDPMC);
	rd32(E1000_CBRMPC);
	rd32(E1000_RPTHC);
	rd32(E1000_HGPTC);
	rd32(E1000_HTCBDPC);
	rd32(E1000_HGORCL);
	rd32(E1000_HGORCH);
	rd32(E1000_HGOTCL);
	rd32(E1000_HGOTCH);
	rd32(E1000_LENERRS);

	/* This register should not be read in copper configurations */
	if (hw->phy.media_type == e1000_media_type_internal_serdes ||
	    igb_sgmii_active_82575(hw))
		rd32(E1000_SCVPC);
}