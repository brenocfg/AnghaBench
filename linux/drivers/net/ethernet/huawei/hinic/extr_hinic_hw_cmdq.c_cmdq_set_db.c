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
typedef  int /*<<< orphan*/  u16 ;
struct hinic_cmdq {int /*<<< orphan*/  db_base; } ;
typedef  enum hinic_cmdq_type { ____Placeholder_hinic_cmdq_type } hinic_cmdq_type ;

/* Variables and functions */
 int /*<<< orphan*/  CMDQ_DB_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmdq_fill_db (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cmdq_set_db(struct hinic_cmdq *cmdq,
			enum hinic_cmdq_type cmdq_type, u16 prod_idx)
{
	u32 db_info;

	cmdq_fill_db(&db_info, cmdq_type, prod_idx);

	/* The data that is written to HW should be in Big Endian Format */
	db_info = cpu_to_be32(db_info);

	wmb();  /* write all before the doorbell */

	writel(db_info, CMDQ_DB_ADDR(cmdq->db_base, prod_idx));
}