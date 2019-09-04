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
typedef  scalar_t__ u32 ;
struct ocrdma_mbx_hdr {int subsys_op; int timeout; scalar_t__ cmd_len; } ;

/* Variables and functions */
 int OCRDMA_MCH_SUBSYS_SHIFT ; 

__attribute__((used)) static void ocrdma_init_mch(struct ocrdma_mbx_hdr *cmd_hdr,
			    u8 opcode, u8 subsys, u32 cmd_len)
{
	cmd_hdr->subsys_op = (opcode | (subsys << OCRDMA_MCH_SUBSYS_SHIFT));
	cmd_hdr->timeout = 20; /* seconds */
	cmd_hdr->cmd_len = cmd_len - sizeof(struct ocrdma_mbx_hdr);
}