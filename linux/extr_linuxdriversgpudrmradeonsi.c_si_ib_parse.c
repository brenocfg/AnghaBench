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
typedef  size_t u32 ;
struct radeon_ib {size_t length_dw; int ring; int /*<<< orphan*/ * ptr; int /*<<< orphan*/  is_const_ib; } ;
struct radeon_device {int /*<<< orphan*/  dev; } ;
struct radeon_cs_packet {size_t idx; int type; int /*<<< orphan*/  count; int /*<<< orphan*/  opcode; scalar_t__ one_reg_wr; } ;

/* Variables and functions */
#define  CAYMAN_RING_TYPE_CP1_INDEX 133 
#define  CAYMAN_RING_TYPE_CP2_INDEX 132 
 int EINVAL ; 
 int /*<<< orphan*/  RADEON_CP_PACKET3_GET_OPCODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RADEON_CP_PACKET_GET_COUNT (int /*<<< orphan*/ ) ; 
 int RADEON_CP_PACKET_GET_TYPE (int /*<<< orphan*/ ) ; 
#define  RADEON_PACKET_TYPE0 131 
#define  RADEON_PACKET_TYPE2 130 
#define  RADEON_PACKET_TYPE3 129 
#define  RADEON_RING_TYPE_GFX_INDEX 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int si_vm_packet3_ce_check (struct radeon_device*,int /*<<< orphan*/ *,struct radeon_cs_packet*) ; 
 int si_vm_packet3_compute_check (struct radeon_device*,int /*<<< orphan*/ *,struct radeon_cs_packet*) ; 
 int si_vm_packet3_gfx_check (struct radeon_device*,int /*<<< orphan*/ *,struct radeon_cs_packet*) ; 

int si_ib_parse(struct radeon_device *rdev, struct radeon_ib *ib)
{
	int ret = 0;
	u32 idx = 0, i;
	struct radeon_cs_packet pkt;

	do {
		pkt.idx = idx;
		pkt.type = RADEON_CP_PACKET_GET_TYPE(ib->ptr[idx]);
		pkt.count = RADEON_CP_PACKET_GET_COUNT(ib->ptr[idx]);
		pkt.one_reg_wr = 0;
		switch (pkt.type) {
		case RADEON_PACKET_TYPE0:
			dev_err(rdev->dev, "Packet0 not allowed!\n");
			ret = -EINVAL;
			break;
		case RADEON_PACKET_TYPE2:
			idx += 1;
			break;
		case RADEON_PACKET_TYPE3:
			pkt.opcode = RADEON_CP_PACKET3_GET_OPCODE(ib->ptr[idx]);
			if (ib->is_const_ib)
				ret = si_vm_packet3_ce_check(rdev, ib->ptr, &pkt);
			else {
				switch (ib->ring) {
				case RADEON_RING_TYPE_GFX_INDEX:
					ret = si_vm_packet3_gfx_check(rdev, ib->ptr, &pkt);
					break;
				case CAYMAN_RING_TYPE_CP1_INDEX:
				case CAYMAN_RING_TYPE_CP2_INDEX:
					ret = si_vm_packet3_compute_check(rdev, ib->ptr, &pkt);
					break;
				default:
					dev_err(rdev->dev, "Non-PM4 ring %d !\n", ib->ring);
					ret = -EINVAL;
					break;
				}
			}
			idx += pkt.count + 2;
			break;
		default:
			dev_err(rdev->dev, "Unknown packet type %d !\n", pkt.type);
			ret = -EINVAL;
			break;
		}
		if (ret) {
			for (i = 0; i < ib->length_dw; i++) {
				if (i == idx)
					printk("\t0x%08x <---\n", ib->ptr[i]);
				else
					printk("\t0x%08x\n", ib->ptr[i]);
			}
			break;
		}
	} while (idx < ib->length_dw);

	return ret;
}