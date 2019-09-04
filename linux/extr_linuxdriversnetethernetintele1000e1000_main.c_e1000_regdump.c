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
struct e1000_hw {int dummy; } ;
struct e1000_adapter {struct e1000_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL ; 
 int /*<<< orphan*/  CTRL_EXT ; 
 int /*<<< orphan*/  ERT ; 
 int NUM_REGS ; 
 int /*<<< orphan*/  RCTL ; 
 int /*<<< orphan*/  RDBAH0 ; 
 int /*<<< orphan*/  RDBAL0 ; 
 int /*<<< orphan*/  RDFH ; 
 int /*<<< orphan*/  RDFHS ; 
 int /*<<< orphan*/  RDFPC ; 
 int /*<<< orphan*/  RDFT ; 
 int /*<<< orphan*/  RDFTS ; 
 int /*<<< orphan*/  RDH ; 
 int /*<<< orphan*/  RDLEN ; 
 int /*<<< orphan*/  RDT ; 
 int /*<<< orphan*/  RDTR ; 
 int /*<<< orphan*/  STATUS ; 
 int /*<<< orphan*/  TADV ; 
 int /*<<< orphan*/  TARC0 ; 
 int /*<<< orphan*/  TARC1 ; 
 int /*<<< orphan*/  TCTL ; 
 int /*<<< orphan*/  TDBAH ; 
 int /*<<< orphan*/  TDBAH1 ; 
 int /*<<< orphan*/  TDBAL ; 
 int /*<<< orphan*/  TDBAL1 ; 
 int /*<<< orphan*/  TDFH ; 
 int /*<<< orphan*/  TDFHS ; 
 int /*<<< orphan*/  TDFPC ; 
 int /*<<< orphan*/  TDFT ; 
 int /*<<< orphan*/  TDFTS ; 
 int /*<<< orphan*/  TDH ; 
 int /*<<< orphan*/  TDH1 ; 
 int /*<<< orphan*/  TDLEN ; 
 int /*<<< orphan*/  TDLEN1 ; 
 int /*<<< orphan*/  TDT ; 
 int /*<<< orphan*/  TDT1 ; 
 int /*<<< orphan*/  TIDV ; 
 int /*<<< orphan*/  TXDCTL ; 
 int /*<<< orphan*/  TXDCTL1 ; 
 int /*<<< orphan*/  er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 

__attribute__((used)) static void e1000_regdump(struct e1000_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;
	u32 regs[NUM_REGS];
	u32 *regs_buff = regs;
	int i = 0;

	static const char * const reg_name[] = {
		"CTRL",  "STATUS",
		"RCTL", "RDLEN", "RDH", "RDT", "RDTR",
		"TCTL", "TDBAL", "TDBAH", "TDLEN", "TDH", "TDT",
		"TIDV", "TXDCTL", "TADV", "TARC0",
		"TDBAL1", "TDBAH1", "TDLEN1", "TDH1", "TDT1",
		"TXDCTL1", "TARC1",
		"CTRL_EXT", "ERT", "RDBAL", "RDBAH",
		"TDFH", "TDFT", "TDFHS", "TDFTS", "TDFPC",
		"RDFH", "RDFT", "RDFHS", "RDFTS", "RDFPC"
	};

	regs_buff[0]  = er32(CTRL);
	regs_buff[1]  = er32(STATUS);

	regs_buff[2]  = er32(RCTL);
	regs_buff[3]  = er32(RDLEN);
	regs_buff[4]  = er32(RDH);
	regs_buff[5]  = er32(RDT);
	regs_buff[6]  = er32(RDTR);

	regs_buff[7]  = er32(TCTL);
	regs_buff[8]  = er32(TDBAL);
	regs_buff[9]  = er32(TDBAH);
	regs_buff[10] = er32(TDLEN);
	regs_buff[11] = er32(TDH);
	regs_buff[12] = er32(TDT);
	regs_buff[13] = er32(TIDV);
	regs_buff[14] = er32(TXDCTL);
	regs_buff[15] = er32(TADV);
	regs_buff[16] = er32(TARC0);

	regs_buff[17] = er32(TDBAL1);
	regs_buff[18] = er32(TDBAH1);
	regs_buff[19] = er32(TDLEN1);
	regs_buff[20] = er32(TDH1);
	regs_buff[21] = er32(TDT1);
	regs_buff[22] = er32(TXDCTL1);
	regs_buff[23] = er32(TARC1);
	regs_buff[24] = er32(CTRL_EXT);
	regs_buff[25] = er32(ERT);
	regs_buff[26] = er32(RDBAL0);
	regs_buff[27] = er32(RDBAH0);
	regs_buff[28] = er32(TDFH);
	regs_buff[29] = er32(TDFT);
	regs_buff[30] = er32(TDFHS);
	regs_buff[31] = er32(TDFTS);
	regs_buff[32] = er32(TDFPC);
	regs_buff[33] = er32(RDFH);
	regs_buff[34] = er32(RDFT);
	regs_buff[35] = er32(RDFHS);
	regs_buff[36] = er32(RDFTS);
	regs_buff[37] = er32(RDFPC);

	pr_info("Register dump\n");
	for (i = 0; i < NUM_REGS; i++)
		pr_info("%-15s  %08x\n", reg_name[i], regs_buff[i]);
}