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

/* Variables and functions */
 int NVME_CMD_EFFECTS_CSE_MASK ; 
 int NVME_CMD_EFFECTS_CSUPP ; 
 int NVME_CMD_EFFECTS_LBCC ; 
#define  nvme_admin_format_nvm 129 
#define  nvme_admin_sanitize_nvm 128 

__attribute__((used)) static u32 nvme_known_admin_effects(u8 opcode)
{
	switch (opcode) {
	case nvme_admin_format_nvm:
		return NVME_CMD_EFFECTS_CSUPP | NVME_CMD_EFFECTS_LBCC |
					NVME_CMD_EFFECTS_CSE_MASK;
	case nvme_admin_sanitize_nvm:
		return NVME_CMD_EFFECTS_CSE_MASK;
	default:
		break;
	}
	return 0;
}