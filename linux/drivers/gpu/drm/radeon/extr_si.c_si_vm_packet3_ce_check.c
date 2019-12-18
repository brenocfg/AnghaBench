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
struct radeon_device {int dummy; } ;
struct radeon_cs_packet {int opcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int EINVAL ; 
#define  PACKET3_CE_WRITE 137 
#define  PACKET3_DUMP_CONST_RAM 136 
#define  PACKET3_INCREMENT_CE_COUNTER 135 
#define  PACKET3_LOAD_CONST_RAM 134 
#define  PACKET3_NOP 133 
#define  PACKET3_SET_BASE 132 
#define  PACKET3_SET_CE_DE_COUNTERS 131 
#define  PACKET3_WAIT_ON_DE_COUNTER 130 
#define  PACKET3_WRITE_CONST_RAM 129 
#define  PACKET3_WRITE_CONST_RAM_OFFSET 128 

__attribute__((used)) static int si_vm_packet3_ce_check(struct radeon_device *rdev,
				  u32 *ib, struct radeon_cs_packet *pkt)
{
	switch (pkt->opcode) {
	case PACKET3_NOP:
	case PACKET3_SET_BASE:
	case PACKET3_SET_CE_DE_COUNTERS:
	case PACKET3_LOAD_CONST_RAM:
	case PACKET3_WRITE_CONST_RAM:
	case PACKET3_WRITE_CONST_RAM_OFFSET:
	case PACKET3_DUMP_CONST_RAM:
	case PACKET3_INCREMENT_CE_COUNTER:
	case PACKET3_WAIT_ON_DE_COUNTER:
	case PACKET3_CE_WRITE:
		break;
	default:
		DRM_ERROR("Invalid CE packet3: 0x%x\n", pkt->opcode);
		return -EINVAL;
	}
	return 0;
}