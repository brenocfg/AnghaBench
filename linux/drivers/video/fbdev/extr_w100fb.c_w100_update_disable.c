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
struct TYPE_2__ {int db_buf_cntl; scalar_t__ en_db_buf; scalar_t__ update_db_buf; } ;
union disp_db_buf_cntl_wr_u {scalar_t__ val; TYPE_1__ f; } ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 scalar_t__ mmDISP_DB_BUF_CNTL ; 
 scalar_t__ remapped_regs ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void w100_update_disable(void)
{
	union disp_db_buf_cntl_wr_u disp_db_buf_wr_cntl;

	/* Prevent display updates */
	disp_db_buf_wr_cntl.f.db_buf_cntl = 0x1e;
	disp_db_buf_wr_cntl.f.update_db_buf = 0;
	disp_db_buf_wr_cntl.f.en_db_buf = 0;
	writel((u32) (disp_db_buf_wr_cntl.val), remapped_regs + mmDISP_DB_BUF_CNTL);
}