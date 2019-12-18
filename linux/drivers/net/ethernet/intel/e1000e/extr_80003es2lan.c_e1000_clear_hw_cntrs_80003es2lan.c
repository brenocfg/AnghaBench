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
 int /*<<< orphan*/  ALGNERRC ; 
 int /*<<< orphan*/  CEXTERR ; 
 int /*<<< orphan*/  IAC ; 
 int /*<<< orphan*/  ICRXATC ; 
 int /*<<< orphan*/  ICRXDMTC ; 
 int /*<<< orphan*/  ICRXOC ; 
 int /*<<< orphan*/  ICRXPTC ; 
 int /*<<< orphan*/  ICTXATC ; 
 int /*<<< orphan*/  ICTXPTC ; 
 int /*<<< orphan*/  ICTXQEC ; 
 int /*<<< orphan*/  ICTXQMTC ; 
 int /*<<< orphan*/  MGTPDC ; 
 int /*<<< orphan*/  MGTPRC ; 
 int /*<<< orphan*/  MGTPTC ; 
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
 int /*<<< orphan*/  RXERRC ; 
 int /*<<< orphan*/  TNCRS ; 
 int /*<<< orphan*/  TSCTC ; 
 int /*<<< orphan*/  TSCTFC ; 
 int /*<<< orphan*/  e1000e_clear_hw_cntrs_base (struct e1000_hw*) ; 
 int /*<<< orphan*/  er32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void e1000_clear_hw_cntrs_80003es2lan(struct e1000_hw *hw)
{
	e1000e_clear_hw_cntrs_base(hw);

	er32(PRC64);
	er32(PRC127);
	er32(PRC255);
	er32(PRC511);
	er32(PRC1023);
	er32(PRC1522);
	er32(PTC64);
	er32(PTC127);
	er32(PTC255);
	er32(PTC511);
	er32(PTC1023);
	er32(PTC1522);

	er32(ALGNERRC);
	er32(RXERRC);
	er32(TNCRS);
	er32(CEXTERR);
	er32(TSCTC);
	er32(TSCTFC);

	er32(MGTPRC);
	er32(MGTPDC);
	er32(MGTPTC);

	er32(IAC);
	er32(ICRXOC);

	er32(ICRXPTC);
	er32(ICRXATC);
	er32(ICTXPTC);
	er32(ICTXATC);
	er32(ICTXQEC);
	er32(ICTXQMTC);
	er32(ICRXDMTC);
}