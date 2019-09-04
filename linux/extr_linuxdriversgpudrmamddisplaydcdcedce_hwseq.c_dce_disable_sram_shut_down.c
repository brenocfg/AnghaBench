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
struct dce_hwseq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_MEM_GLOBAL_PWR_REQ_CNTL ; 
 int /*<<< orphan*/  DC_MEM_GLOBAL_PWR_REQ_DIS ; 
 scalar_t__ REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dce_disable_sram_shut_down(struct dce_hwseq *hws)
{
	if (REG(DC_MEM_GLOBAL_PWR_REQ_CNTL))
		REG_UPDATE(DC_MEM_GLOBAL_PWR_REQ_CNTL,
				DC_MEM_GLOBAL_PWR_REQ_DIS, 1);
}