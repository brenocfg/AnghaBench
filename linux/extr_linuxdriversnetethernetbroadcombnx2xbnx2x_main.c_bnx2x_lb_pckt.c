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
typedef  int u32 ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NIG_REG_DEBUG_PACKET_LB ; 
 int /*<<< orphan*/  REG_WR_DMAE (struct bnx2x*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void bnx2x_lb_pckt(struct bnx2x *bp)
{
	u32 wb_write[3];

	/* Ethernet source and destination addresses */
	wb_write[0] = 0x55555555;
	wb_write[1] = 0x55555555;
	wb_write[2] = 0x20;		/* SOP */
	REG_WR_DMAE(bp, NIG_REG_DEBUG_PACKET_LB, wb_write, 3);

	/* NON-IP protocol */
	wb_write[0] = 0x09000000;
	wb_write[1] = 0x55555555;
	wb_write[2] = 0x10;		/* EOP, eop_bvalid = 0 */
	REG_WR_DMAE(bp, NIG_REG_DEBUG_PACKET_LB, wb_write, 3);
}