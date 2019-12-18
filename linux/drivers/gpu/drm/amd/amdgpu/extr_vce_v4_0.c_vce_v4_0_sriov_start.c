#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_13__ ;
typedef  struct TYPE_16__   TYPE_12__ ;
typedef  struct TYPE_15__   TYPE_11__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int uint32_t ;
struct mmsch_v1_0_init_header {int vce_table_offset; scalar_t__ vce_table_size; int header_size; int uvd_table_offset; int uvd_table_size; int /*<<< orphan*/  version; } ;
struct TYPE_26__ {int /*<<< orphan*/  command_type; } ;
struct TYPE_21__ {int /*<<< orphan*/  member_0; } ;
struct mmsch_v1_0_cmd_end {TYPE_9__ cmd_header; TYPE_4__ member_0; } ;
struct TYPE_23__ {int /*<<< orphan*/  command_type; } ;
struct TYPE_18__ {int /*<<< orphan*/  member_0; } ;
struct mmsch_v1_0_cmd_direct_write {TYPE_6__ cmd_header; TYPE_1__ member_0; } ;
struct TYPE_24__ {int /*<<< orphan*/  command_type; } ;
struct TYPE_19__ {int /*<<< orphan*/  member_0; } ;
struct mmsch_v1_0_cmd_direct_read_modify_write {TYPE_7__ cmd_header; TYPE_2__ member_0; } ;
struct TYPE_25__ {int /*<<< orphan*/  command_type; } ;
struct TYPE_20__ {int /*<<< orphan*/  member_0; } ;
struct mmsch_v1_0_cmd_direct_polling {TYPE_8__ cmd_header; TYPE_3__ member_0; } ;
struct amdgpu_ring {int ring_size; int /*<<< orphan*/  gpu_addr; } ;
struct TYPE_17__ {int* cpu_addr; } ;
struct TYPE_22__ {TYPE_13__ mm_table; } ;
struct TYPE_16__ {scalar_t__ load_type; TYPE_10__* ucode; } ;
struct TYPE_15__ {int gpu_addr; struct amdgpu_ring* ring; } ;
struct amdgpu_device {TYPE_5__ virt; TYPE_12__ firmware; TYPE_11__ vce; } ;
struct TYPE_14__ {int tmr_mc_addr_lo; int tmr_mc_addr_hi; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_FW_LOAD_PSP ; 
 size_t AMDGPU_UCODE_ID_VCE ; 
 int AMDGPU_VCE_FIRMWARE_OFFSET ; 
 int /*<<< orphan*/  MMSCH_COMMAND__DIRECT_REG_POLLING ; 
 int /*<<< orphan*/  MMSCH_COMMAND__DIRECT_REG_READ_MODIFY_WRITE ; 
 int /*<<< orphan*/  MMSCH_COMMAND__DIRECT_REG_WRITE ; 
 int /*<<< orphan*/  MMSCH_COMMAND__END ; 
 int /*<<< orphan*/  MMSCH_V1_0_INSERT_DIRECT_POLL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MMSCH_V1_0_INSERT_DIRECT_RD_MOD_WT (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  MMSCH_V1_0_INSERT_DIRECT_WT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MMSCH_VERSION ; 
 int /*<<< orphan*/  SOC15_REG_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VCE ; 
 int VCE_SOFT_RESET__ECPU_SOFT_RESET_MASK ; 
 int /*<<< orphan*/  VCE_STATUS_VCPU_REPORT_FW_LOADED_MASK ; 
 int VCE_STATUS__JOB_BUSY_MASK ; 
 int VCE_SYS_INT_EN__VCE_SYS_INT_TRAP_INTERRUPT_EN_MASK ; 
 int VCE_V4_0_DATA_SIZE ; 
 int VCE_V4_0_FW_SIZE ; 
 int VCE_V4_0_STACK_SIZE ; 
 int VCE_VCPU_CNTL__CLK_EN_MASK ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,struct mmsch_v1_0_cmd_end*,int) ; 
 int /*<<< orphan*/  mmVCE_LMI_CACHE_CTRL ; 
 int /*<<< orphan*/  mmVCE_LMI_CTRL ; 
 int /*<<< orphan*/  mmVCE_LMI_CTRL2 ; 
 int /*<<< orphan*/  mmVCE_LMI_SWAP_CNTL ; 
 int /*<<< orphan*/  mmVCE_LMI_SWAP_CNTL1 ; 
 int /*<<< orphan*/  mmVCE_LMI_VCPU_CACHE_40BIT_BAR0 ; 
 int /*<<< orphan*/  mmVCE_LMI_VCPU_CACHE_40BIT_BAR1 ; 
 int /*<<< orphan*/  mmVCE_LMI_VCPU_CACHE_40BIT_BAR2 ; 
 int /*<<< orphan*/  mmVCE_LMI_VCPU_CACHE_64BIT_BAR0 ; 
 int /*<<< orphan*/  mmVCE_LMI_VCPU_CACHE_64BIT_BAR1 ; 
 int /*<<< orphan*/  mmVCE_LMI_VCPU_CACHE_64BIT_BAR2 ; 
 int /*<<< orphan*/  mmVCE_LMI_VM_CTRL ; 
 int /*<<< orphan*/  mmVCE_RB_BASE_HI ; 
 int /*<<< orphan*/  mmVCE_RB_BASE_LO ; 
 int /*<<< orphan*/  mmVCE_RB_SIZE ; 
 int /*<<< orphan*/  mmVCE_SOFT_RESET ; 
 int /*<<< orphan*/  mmVCE_STATUS ; 
 int /*<<< orphan*/  mmVCE_SYS_INT_EN ; 
 int /*<<< orphan*/  mmVCE_VCPU_CACHE_OFFSET0 ; 
 int /*<<< orphan*/  mmVCE_VCPU_CACHE_OFFSET1 ; 
 int /*<<< orphan*/  mmVCE_VCPU_CACHE_OFFSET2 ; 
 int /*<<< orphan*/  mmVCE_VCPU_CACHE_SIZE0 ; 
 int /*<<< orphan*/  mmVCE_VCPU_CACHE_SIZE1 ; 
 int /*<<< orphan*/  mmVCE_VCPU_CACHE_SIZE2 ; 
 int /*<<< orphan*/  mmVCE_VCPU_CNTL ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 
 int vce_v4_0_mmsch_start (struct amdgpu_device*,TYPE_13__*) ; 

__attribute__((used)) static int vce_v4_0_sriov_start(struct amdgpu_device *adev)
{
	struct amdgpu_ring *ring;
	uint32_t offset, size;
	uint32_t table_size = 0;
	struct mmsch_v1_0_cmd_direct_write direct_wt = { { 0 } };
	struct mmsch_v1_0_cmd_direct_read_modify_write direct_rd_mod_wt = { { 0 } };
	struct mmsch_v1_0_cmd_direct_polling direct_poll = { { 0 } };
	struct mmsch_v1_0_cmd_end end = { { 0 } };
	uint32_t *init_table = adev->virt.mm_table.cpu_addr;
	struct mmsch_v1_0_init_header *header = (struct mmsch_v1_0_init_header *)init_table;

	direct_wt.cmd_header.command_type = MMSCH_COMMAND__DIRECT_REG_WRITE;
	direct_rd_mod_wt.cmd_header.command_type = MMSCH_COMMAND__DIRECT_REG_READ_MODIFY_WRITE;
	direct_poll.cmd_header.command_type = MMSCH_COMMAND__DIRECT_REG_POLLING;
	end.cmd_header.command_type = MMSCH_COMMAND__END;

	if (header->vce_table_offset == 0 && header->vce_table_size == 0) {
		header->version = MMSCH_VERSION;
		header->header_size = sizeof(struct mmsch_v1_0_init_header) >> 2;

		if (header->uvd_table_offset == 0 && header->uvd_table_size == 0)
			header->vce_table_offset = header->header_size;
		else
			header->vce_table_offset = header->uvd_table_size + header->uvd_table_offset;

		init_table += header->vce_table_offset;

		ring = &adev->vce.ring[0];
		MMSCH_V1_0_INSERT_DIRECT_WT(SOC15_REG_OFFSET(VCE, 0, mmVCE_RB_BASE_LO),
					    lower_32_bits(ring->gpu_addr));
		MMSCH_V1_0_INSERT_DIRECT_WT(SOC15_REG_OFFSET(VCE, 0, mmVCE_RB_BASE_HI),
					    upper_32_bits(ring->gpu_addr));
		MMSCH_V1_0_INSERT_DIRECT_WT(SOC15_REG_OFFSET(VCE, 0, mmVCE_RB_SIZE),
					    ring->ring_size / 4);

		/* BEGING OF MC_RESUME */
		MMSCH_V1_0_INSERT_DIRECT_WT(SOC15_REG_OFFSET(VCE, 0, mmVCE_LMI_CTRL), 0x398000);
		MMSCH_V1_0_INSERT_DIRECT_RD_MOD_WT(SOC15_REG_OFFSET(VCE, 0, mmVCE_LMI_CACHE_CTRL), ~0x1, 0);
		MMSCH_V1_0_INSERT_DIRECT_WT(SOC15_REG_OFFSET(VCE, 0, mmVCE_LMI_SWAP_CNTL), 0);
		MMSCH_V1_0_INSERT_DIRECT_WT(SOC15_REG_OFFSET(VCE, 0, mmVCE_LMI_SWAP_CNTL1), 0);
		MMSCH_V1_0_INSERT_DIRECT_WT(SOC15_REG_OFFSET(VCE, 0, mmVCE_LMI_VM_CTRL), 0);

		offset = AMDGPU_VCE_FIRMWARE_OFFSET;
		if (adev->firmware.load_type == AMDGPU_FW_LOAD_PSP) {
			uint32_t low = adev->firmware.ucode[AMDGPU_UCODE_ID_VCE].tmr_mc_addr_lo;
			uint32_t hi = adev->firmware.ucode[AMDGPU_UCODE_ID_VCE].tmr_mc_addr_hi;
			uint64_t tmr_mc_addr = (uint64_t)(hi) << 32 | low;

			MMSCH_V1_0_INSERT_DIRECT_WT(SOC15_REG_OFFSET(VCE, 0,
						mmVCE_LMI_VCPU_CACHE_40BIT_BAR0), tmr_mc_addr >> 8);
			MMSCH_V1_0_INSERT_DIRECT_WT(SOC15_REG_OFFSET(VCE, 0,
						mmVCE_LMI_VCPU_CACHE_64BIT_BAR0),
						(tmr_mc_addr >> 40) & 0xff);
			MMSCH_V1_0_INSERT_DIRECT_WT(SOC15_REG_OFFSET(VCE, 0, mmVCE_VCPU_CACHE_OFFSET0), 0);
		} else {
			MMSCH_V1_0_INSERT_DIRECT_WT(SOC15_REG_OFFSET(VCE, 0,
						mmVCE_LMI_VCPU_CACHE_40BIT_BAR0),
						adev->vce.gpu_addr >> 8);
			MMSCH_V1_0_INSERT_DIRECT_WT(SOC15_REG_OFFSET(VCE, 0,
						mmVCE_LMI_VCPU_CACHE_64BIT_BAR0),
						(adev->vce.gpu_addr >> 40) & 0xff);
			MMSCH_V1_0_INSERT_DIRECT_WT(SOC15_REG_OFFSET(VCE, 0, mmVCE_VCPU_CACHE_OFFSET0),
						offset & ~0x0f000000);

		}
		MMSCH_V1_0_INSERT_DIRECT_WT(SOC15_REG_OFFSET(VCE, 0,
						mmVCE_LMI_VCPU_CACHE_40BIT_BAR1),
						adev->vce.gpu_addr >> 8);
		MMSCH_V1_0_INSERT_DIRECT_WT(SOC15_REG_OFFSET(VCE, 0,
						mmVCE_LMI_VCPU_CACHE_64BIT_BAR1),
						(adev->vce.gpu_addr >> 40) & 0xff);
		MMSCH_V1_0_INSERT_DIRECT_WT(SOC15_REG_OFFSET(VCE, 0,
						mmVCE_LMI_VCPU_CACHE_40BIT_BAR2),
						adev->vce.gpu_addr >> 8);
		MMSCH_V1_0_INSERT_DIRECT_WT(SOC15_REG_OFFSET(VCE, 0,
						mmVCE_LMI_VCPU_CACHE_64BIT_BAR2),
						(adev->vce.gpu_addr >> 40) & 0xff);

		size = VCE_V4_0_FW_SIZE;
		MMSCH_V1_0_INSERT_DIRECT_WT(SOC15_REG_OFFSET(VCE, 0, mmVCE_VCPU_CACHE_SIZE0), size);

		offset = (adev->firmware.load_type != AMDGPU_FW_LOAD_PSP) ? offset + size : 0;
		size = VCE_V4_0_STACK_SIZE;
		MMSCH_V1_0_INSERT_DIRECT_WT(SOC15_REG_OFFSET(VCE, 0, mmVCE_VCPU_CACHE_OFFSET1),
					(offset & ~0x0f000000) | (1 << 24));
		MMSCH_V1_0_INSERT_DIRECT_WT(SOC15_REG_OFFSET(VCE, 0, mmVCE_VCPU_CACHE_SIZE1), size);

		offset += size;
		size = VCE_V4_0_DATA_SIZE;
		MMSCH_V1_0_INSERT_DIRECT_WT(SOC15_REG_OFFSET(VCE, 0, mmVCE_VCPU_CACHE_OFFSET2),
					(offset & ~0x0f000000) | (2 << 24));
		MMSCH_V1_0_INSERT_DIRECT_WT(SOC15_REG_OFFSET(VCE, 0, mmVCE_VCPU_CACHE_SIZE2), size);

		MMSCH_V1_0_INSERT_DIRECT_RD_MOD_WT(SOC15_REG_OFFSET(VCE, 0, mmVCE_LMI_CTRL2), ~0x100, 0);
		MMSCH_V1_0_INSERT_DIRECT_RD_MOD_WT(SOC15_REG_OFFSET(VCE, 0, mmVCE_SYS_INT_EN),
						   VCE_SYS_INT_EN__VCE_SYS_INT_TRAP_INTERRUPT_EN_MASK,
						   VCE_SYS_INT_EN__VCE_SYS_INT_TRAP_INTERRUPT_EN_MASK);

		/* end of MC_RESUME */
		MMSCH_V1_0_INSERT_DIRECT_RD_MOD_WT(SOC15_REG_OFFSET(VCE, 0, mmVCE_STATUS),
						   VCE_STATUS__JOB_BUSY_MASK, ~VCE_STATUS__JOB_BUSY_MASK);
		MMSCH_V1_0_INSERT_DIRECT_RD_MOD_WT(SOC15_REG_OFFSET(VCE, 0, mmVCE_VCPU_CNTL),
						   ~0x200001, VCE_VCPU_CNTL__CLK_EN_MASK);
		MMSCH_V1_0_INSERT_DIRECT_RD_MOD_WT(SOC15_REG_OFFSET(VCE, 0, mmVCE_SOFT_RESET),
						   ~VCE_SOFT_RESET__ECPU_SOFT_RESET_MASK, 0);

		MMSCH_V1_0_INSERT_DIRECT_POLL(SOC15_REG_OFFSET(VCE, 0, mmVCE_STATUS),
					      VCE_STATUS_VCPU_REPORT_FW_LOADED_MASK,
					      VCE_STATUS_VCPU_REPORT_FW_LOADED_MASK);

		/* clear BUSY flag */
		MMSCH_V1_0_INSERT_DIRECT_RD_MOD_WT(SOC15_REG_OFFSET(VCE, 0, mmVCE_STATUS),
						   ~VCE_STATUS__JOB_BUSY_MASK, 0);

		/* add end packet */
		memcpy((void *)init_table, &end, sizeof(struct mmsch_v1_0_cmd_end));
		table_size += sizeof(struct mmsch_v1_0_cmd_end) / 4;
		header->vce_table_size = table_size;
	}

	return vce_v4_0_mmsch_start(adev, &adev->virt.mm_table);
}