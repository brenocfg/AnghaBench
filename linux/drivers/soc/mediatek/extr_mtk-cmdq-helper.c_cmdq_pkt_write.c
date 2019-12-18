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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct cmdq_pkt {int dummy; } ;

/* Variables and functions */
 int CMDQ_ARG_A_WRITE_MASK ; 
 int /*<<< orphan*/  CMDQ_CODE_WRITE ; 
 int CMDQ_SUBSYS_SHIFT ; 
 int cmdq_pkt_append_command (struct cmdq_pkt*,int /*<<< orphan*/ ,int,int) ; 

int cmdq_pkt_write(struct cmdq_pkt *pkt, u8 subsys, u16 offset, u32 value)
{
	u32 arg_a = (offset & CMDQ_ARG_A_WRITE_MASK) |
		    (subsys << CMDQ_SUBSYS_SHIFT);

	return cmdq_pkt_append_command(pkt, CMDQ_CODE_WRITE, arg_a, value);
}