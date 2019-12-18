#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_15__ ;
typedef  struct TYPE_20__   TYPE_14__ ;
typedef  struct TYPE_19__   TYPE_13__ ;
typedef  struct TYPE_18__   TYPE_12__ ;
typedef  struct TYPE_17__   TYPE_11__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct mmsch_v1_0_init_header {int uvd_table_offset; scalar_t__ uvd_table_size; int header_size; int vce_table_offset; int vce_table_size; int /*<<< orphan*/  version; } ;
struct TYPE_30__ {int /*<<< orphan*/  command_type; } ;
struct TYPE_25__ {int /*<<< orphan*/  member_0; } ;
struct mmsch_v1_0_cmd_end {TYPE_9__ cmd_header; TYPE_4__ member_0; } ;
struct TYPE_27__ {int /*<<< orphan*/  command_type; } ;
struct TYPE_22__ {int /*<<< orphan*/  member_0; } ;
struct mmsch_v1_0_cmd_direct_write {TYPE_6__ cmd_header; TYPE_1__ member_0; } ;
struct TYPE_28__ {int /*<<< orphan*/  command_type; } ;
struct TYPE_23__ {int /*<<< orphan*/  member_0; } ;
struct mmsch_v1_0_cmd_direct_read_modify_write {TYPE_7__ cmd_header; TYPE_2__ member_0; } ;
struct TYPE_29__ {int /*<<< orphan*/  command_type; } ;
struct TYPE_24__ {int /*<<< orphan*/  member_0; } ;
struct mmsch_v1_0_cmd_direct_polling {TYPE_8__ cmd_header; TYPE_3__ member_0; } ;
struct amdgpu_ring {int ring_size; int gpu_addr; scalar_t__ wptr; } ;
struct TYPE_21__ {int* cpu_addr; } ;
struct TYPE_26__ {TYPE_15__ mm_table; } ;
struct TYPE_20__ {int num_uvd_inst; int harvest_config; int max_handles; TYPE_13__* inst; TYPE_10__* fw; } ;
struct TYPE_18__ {scalar_t__ load_type; TYPE_11__* ucode; } ;
struct amdgpu_device {TYPE_5__ virt; TYPE_14__ uvd; TYPE_12__ firmware; } ;
struct TYPE_19__ {int gpu_addr; struct amdgpu_ring* ring_enc; struct amdgpu_ring ring; } ;
struct TYPE_17__ {int tmr_mc_addr_lo; int tmr_mc_addr_hi; } ;
struct TYPE_16__ {scalar_t__ size; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_FW_LOAD_PSP ; 
 int AMDGPU_GPU_PAGE_ALIGN (scalar_t__) ; 
 size_t AMDGPU_UCODE_ID_UVD ; 
 int AMDGPU_UVD_FIRMWARE_OFFSET ; 
 int AMDGPU_UVD_HEAP_SIZE ; 
 int AMDGPU_UVD_SESSION_SIZE ; 
 int AMDGPU_UVD_STACK_SIZE ; 
 int /*<<< orphan*/  MMSCH_COMMAND__DIRECT_REG_POLLING ; 
 int /*<<< orphan*/  MMSCH_COMMAND__DIRECT_REG_READ_MODIFY_WRITE ; 
 int /*<<< orphan*/  MMSCH_COMMAND__DIRECT_REG_WRITE ; 
 int /*<<< orphan*/  MMSCH_COMMAND__END ; 
 int /*<<< orphan*/  MMSCH_V1_0_INSERT_DIRECT_POLL (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  MMSCH_V1_0_INSERT_DIRECT_RD_MOD_WT (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  MMSCH_V1_0_INSERT_DIRECT_WT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MMSCH_VERSION ; 
 int /*<<< orphan*/  RB_BUFSZ ; 
 int /*<<< orphan*/  RB_NO_FETCH ; 
 int REG_SET_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SOC15_REG_OFFSET (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UVD ; 
 int UVD_CGC_CTRL__DYN_CLOCK_MODE_MASK ; 
 int UVD_LMI_CTRL2__STALL_ARB_UMC_MASK ; 
 int UVD_LMI_CTRL__DATA_COHERENCY_EN_MASK ; 
 int UVD_LMI_CTRL__REQ_MODE_MASK ; 
 int UVD_LMI_CTRL__VCPU_DATA_COHERENCY_EN_MASK ; 
 int UVD_LMI_CTRL__WRITE_CLEAN_TIMER_EN_MASK ; 
 int UVD_LMI_CTRL__WRITE_CLEAN_TIMER__SHIFT ; 
 int UVD_MASTINT_EN__SYS_EN_MASK ; 
 int UVD_MASTINT_EN__VCPU_EN_MASK ; 
 int /*<<< orphan*/  UVD_RBC_RB_CNTL ; 
 int UVD_SOFT_RESET__CSM_SOFT_RESET_MASK ; 
 int UVD_SOFT_RESET__CXW_SOFT_RESET_MASK ; 
 int UVD_SOFT_RESET__LBSI_SOFT_RESET_MASK ; 
 int UVD_SOFT_RESET__LMI_SOFT_RESET_MASK ; 
 int UVD_SOFT_RESET__LMI_UMC_SOFT_RESET_MASK ; 
 int UVD_SOFT_RESET__RBC_SOFT_RESET_MASK ; 
 int UVD_SOFT_RESET__TAP_SOFT_RESET_MASK ; 
 int UVD_SOFT_RESET__VCPU_SOFT_RESET_MASK ; 
 int UVD_STATUS__VCPU_REPORT__SHIFT ; 
 int UVD_VCPU_CNTL__CLK_EN_MASK ; 
 int lower_32_bits (int) ; 
 int /*<<< orphan*/  memcpy (void*,struct mmsch_v1_0_cmd_end*,int) ; 
 int /*<<< orphan*/  mmUVD_CGC_CTRL ; 
 int /*<<< orphan*/  mmUVD_GP_SCRATCH4 ; 
 int /*<<< orphan*/  mmUVD_LMI_CTRL ; 
 int /*<<< orphan*/  mmUVD_LMI_CTRL2 ; 
 int /*<<< orphan*/  mmUVD_LMI_VCPU_CACHE1_64BIT_BAR_HIGH ; 
 int /*<<< orphan*/  mmUVD_LMI_VCPU_CACHE1_64BIT_BAR_LOW ; 
 int /*<<< orphan*/  mmUVD_LMI_VCPU_CACHE2_64BIT_BAR_HIGH ; 
 int /*<<< orphan*/  mmUVD_LMI_VCPU_CACHE2_64BIT_BAR_LOW ; 
 int /*<<< orphan*/  mmUVD_LMI_VCPU_CACHE_64BIT_BAR_HIGH ; 
 int /*<<< orphan*/  mmUVD_LMI_VCPU_CACHE_64BIT_BAR_LOW ; 
 int /*<<< orphan*/  mmUVD_MASTINT_EN ; 
 int /*<<< orphan*/  mmUVD_RBC_RB_CNTL ; 
 int /*<<< orphan*/  mmUVD_RB_BASE_HI ; 
 int /*<<< orphan*/  mmUVD_RB_BASE_LO ; 
 int /*<<< orphan*/  mmUVD_RB_SIZE ; 
 int /*<<< orphan*/  mmUVD_SOFT_RESET ; 
 int /*<<< orphan*/  mmUVD_STATUS ; 
 int /*<<< orphan*/  mmUVD_VCPU_CACHE_OFFSET0 ; 
 int /*<<< orphan*/  mmUVD_VCPU_CACHE_OFFSET1 ; 
 int /*<<< orphan*/  mmUVD_VCPU_CACHE_OFFSET2 ; 
 int /*<<< orphan*/  mmUVD_VCPU_CACHE_SIZE0 ; 
 int /*<<< orphan*/  mmUVD_VCPU_CACHE_SIZE1 ; 
 int /*<<< orphan*/  mmUVD_VCPU_CACHE_SIZE2 ; 
 int /*<<< orphan*/  mmUVD_VCPU_CNTL ; 
 int order_base_2 (int) ; 
 int upper_32_bits (int) ; 
 int uvd_v7_0_mmsch_start (struct amdgpu_device*,TYPE_15__*) ; 

__attribute__((used)) static int uvd_v7_0_sriov_start(struct amdgpu_device *adev)
{
	struct amdgpu_ring *ring;
	uint32_t offset, size, tmp;
	uint32_t table_size = 0;
	struct mmsch_v1_0_cmd_direct_write direct_wt = { {0} };
	struct mmsch_v1_0_cmd_direct_read_modify_write direct_rd_mod_wt = { {0} };
	struct mmsch_v1_0_cmd_direct_polling direct_poll = { {0} };
	struct mmsch_v1_0_cmd_end end = { {0} };
	uint32_t *init_table = adev->virt.mm_table.cpu_addr;
	struct mmsch_v1_0_init_header *header = (struct mmsch_v1_0_init_header *)init_table;
	uint8_t i = 0;

	direct_wt.cmd_header.command_type = MMSCH_COMMAND__DIRECT_REG_WRITE;
	direct_rd_mod_wt.cmd_header.command_type = MMSCH_COMMAND__DIRECT_REG_READ_MODIFY_WRITE;
	direct_poll.cmd_header.command_type = MMSCH_COMMAND__DIRECT_REG_POLLING;
	end.cmd_header.command_type = MMSCH_COMMAND__END;

	if (header->uvd_table_offset == 0 && header->uvd_table_size == 0) {
		header->version = MMSCH_VERSION;
		header->header_size = sizeof(struct mmsch_v1_0_init_header) >> 2;

		if (header->vce_table_offset == 0 && header->vce_table_size == 0)
			header->uvd_table_offset = header->header_size;
		else
			header->uvd_table_offset = header->vce_table_size + header->vce_table_offset;

		init_table += header->uvd_table_offset;

		for (i = 0; i < adev->uvd.num_uvd_inst; ++i) {
			if (adev->uvd.harvest_config & (1 << i))
				continue;
			ring = &adev->uvd.inst[i].ring;
			ring->wptr = 0;
			size = AMDGPU_GPU_PAGE_ALIGN(adev->uvd.fw->size + 4);

			MMSCH_V1_0_INSERT_DIRECT_RD_MOD_WT(SOC15_REG_OFFSET(UVD, i, mmUVD_STATUS),
							   0xFFFFFFFF, 0x00000004);
			/* mc resume*/
			if (adev->firmware.load_type == AMDGPU_FW_LOAD_PSP) {
				MMSCH_V1_0_INSERT_DIRECT_WT(SOC15_REG_OFFSET(UVD, i,
							mmUVD_LMI_VCPU_CACHE_64BIT_BAR_LOW),
							adev->firmware.ucode[AMDGPU_UCODE_ID_UVD].tmr_mc_addr_lo);
				MMSCH_V1_0_INSERT_DIRECT_WT(SOC15_REG_OFFSET(UVD, i,
							mmUVD_LMI_VCPU_CACHE_64BIT_BAR_HIGH),
							adev->firmware.ucode[AMDGPU_UCODE_ID_UVD].tmr_mc_addr_hi);
				MMSCH_V1_0_INSERT_DIRECT_WT(SOC15_REG_OFFSET(UVD, 0, mmUVD_VCPU_CACHE_OFFSET0), 0);
				offset = 0;
			} else {
				MMSCH_V1_0_INSERT_DIRECT_WT(SOC15_REG_OFFSET(UVD, i, mmUVD_LMI_VCPU_CACHE_64BIT_BAR_LOW),
							    lower_32_bits(adev->uvd.inst[i].gpu_addr));
				MMSCH_V1_0_INSERT_DIRECT_WT(SOC15_REG_OFFSET(UVD, i, mmUVD_LMI_VCPU_CACHE_64BIT_BAR_HIGH),
							    upper_32_bits(adev->uvd.inst[i].gpu_addr));
				offset = size;
				MMSCH_V1_0_INSERT_DIRECT_WT(SOC15_REG_OFFSET(UVD, 0, mmUVD_VCPU_CACHE_OFFSET0),
							AMDGPU_UVD_FIRMWARE_OFFSET >> 3);

			}

			MMSCH_V1_0_INSERT_DIRECT_WT(SOC15_REG_OFFSET(UVD, i, mmUVD_VCPU_CACHE_SIZE0), size);

			MMSCH_V1_0_INSERT_DIRECT_WT(SOC15_REG_OFFSET(UVD, i, mmUVD_LMI_VCPU_CACHE1_64BIT_BAR_LOW),
						    lower_32_bits(adev->uvd.inst[i].gpu_addr + offset));
			MMSCH_V1_0_INSERT_DIRECT_WT(SOC15_REG_OFFSET(UVD, i, mmUVD_LMI_VCPU_CACHE1_64BIT_BAR_HIGH),
						    upper_32_bits(adev->uvd.inst[i].gpu_addr + offset));
			MMSCH_V1_0_INSERT_DIRECT_WT(SOC15_REG_OFFSET(UVD, i, mmUVD_VCPU_CACHE_OFFSET1), (1 << 21));
			MMSCH_V1_0_INSERT_DIRECT_WT(SOC15_REG_OFFSET(UVD, i, mmUVD_VCPU_CACHE_SIZE1), AMDGPU_UVD_HEAP_SIZE);

			MMSCH_V1_0_INSERT_DIRECT_WT(SOC15_REG_OFFSET(UVD, i, mmUVD_LMI_VCPU_CACHE2_64BIT_BAR_LOW),
						    lower_32_bits(adev->uvd.inst[i].gpu_addr + offset + AMDGPU_UVD_HEAP_SIZE));
			MMSCH_V1_0_INSERT_DIRECT_WT(SOC15_REG_OFFSET(UVD, i, mmUVD_LMI_VCPU_CACHE2_64BIT_BAR_HIGH),
						    upper_32_bits(adev->uvd.inst[i].gpu_addr + offset + AMDGPU_UVD_HEAP_SIZE));
			MMSCH_V1_0_INSERT_DIRECT_WT(SOC15_REG_OFFSET(UVD, i, mmUVD_VCPU_CACHE_OFFSET2), (2 << 21));
			MMSCH_V1_0_INSERT_DIRECT_WT(SOC15_REG_OFFSET(UVD, i, mmUVD_VCPU_CACHE_SIZE2),
						    AMDGPU_UVD_STACK_SIZE + (AMDGPU_UVD_SESSION_SIZE * 40));

			MMSCH_V1_0_INSERT_DIRECT_WT(SOC15_REG_OFFSET(UVD, i, mmUVD_GP_SCRATCH4), adev->uvd.max_handles);
			/* mc resume end*/

			/* disable clock gating */
			MMSCH_V1_0_INSERT_DIRECT_RD_MOD_WT(SOC15_REG_OFFSET(UVD, i, mmUVD_CGC_CTRL),
							   ~UVD_CGC_CTRL__DYN_CLOCK_MODE_MASK, 0);

			/* disable interupt */
			MMSCH_V1_0_INSERT_DIRECT_RD_MOD_WT(SOC15_REG_OFFSET(UVD, i, mmUVD_MASTINT_EN),
							   ~UVD_MASTINT_EN__VCPU_EN_MASK, 0);

			/* stall UMC and register bus before resetting VCPU */
			MMSCH_V1_0_INSERT_DIRECT_RD_MOD_WT(SOC15_REG_OFFSET(UVD, i, mmUVD_LMI_CTRL2),
							   ~UVD_LMI_CTRL2__STALL_ARB_UMC_MASK,
							   UVD_LMI_CTRL2__STALL_ARB_UMC_MASK);

			/* put LMI, VCPU, RBC etc... into reset */
			MMSCH_V1_0_INSERT_DIRECT_WT(SOC15_REG_OFFSET(UVD, i, mmUVD_SOFT_RESET),
						    (uint32_t)(UVD_SOFT_RESET__LMI_SOFT_RESET_MASK |
							       UVD_SOFT_RESET__VCPU_SOFT_RESET_MASK |
							       UVD_SOFT_RESET__LBSI_SOFT_RESET_MASK |
							       UVD_SOFT_RESET__RBC_SOFT_RESET_MASK |
							       UVD_SOFT_RESET__CSM_SOFT_RESET_MASK |
							       UVD_SOFT_RESET__CXW_SOFT_RESET_MASK |
							       UVD_SOFT_RESET__TAP_SOFT_RESET_MASK |
							       UVD_SOFT_RESET__LMI_UMC_SOFT_RESET_MASK));

			/* initialize UVD memory controller */
			MMSCH_V1_0_INSERT_DIRECT_WT(SOC15_REG_OFFSET(UVD, i, mmUVD_LMI_CTRL),
						    (uint32_t)((0x40 << UVD_LMI_CTRL__WRITE_CLEAN_TIMER__SHIFT) |
							       UVD_LMI_CTRL__WRITE_CLEAN_TIMER_EN_MASK |
							       UVD_LMI_CTRL__DATA_COHERENCY_EN_MASK |
							       UVD_LMI_CTRL__VCPU_DATA_COHERENCY_EN_MASK |
							       UVD_LMI_CTRL__REQ_MODE_MASK |
							       0x00100000L));

			/* take all subblocks out of reset, except VCPU */
			MMSCH_V1_0_INSERT_DIRECT_WT(SOC15_REG_OFFSET(UVD, i, mmUVD_SOFT_RESET),
						    UVD_SOFT_RESET__VCPU_SOFT_RESET_MASK);

			/* enable VCPU clock */
			MMSCH_V1_0_INSERT_DIRECT_WT(SOC15_REG_OFFSET(UVD, i, mmUVD_VCPU_CNTL),
						    UVD_VCPU_CNTL__CLK_EN_MASK);

			/* enable master interrupt */
			MMSCH_V1_0_INSERT_DIRECT_RD_MOD_WT(SOC15_REG_OFFSET(UVD, i, mmUVD_MASTINT_EN),
							   ~(UVD_MASTINT_EN__VCPU_EN_MASK|UVD_MASTINT_EN__SYS_EN_MASK),
							   (UVD_MASTINT_EN__VCPU_EN_MASK|UVD_MASTINT_EN__SYS_EN_MASK));

			/* clear the bit 4 of UVD_STATUS */
			MMSCH_V1_0_INSERT_DIRECT_RD_MOD_WT(SOC15_REG_OFFSET(UVD, i, mmUVD_STATUS),
							   ~(2 << UVD_STATUS__VCPU_REPORT__SHIFT), 0);

			/* force RBC into idle state */
			size = order_base_2(ring->ring_size);
			tmp = REG_SET_FIELD(0, UVD_RBC_RB_CNTL, RB_BUFSZ, size);
			tmp = REG_SET_FIELD(tmp, UVD_RBC_RB_CNTL, RB_NO_FETCH, 1);
			MMSCH_V1_0_INSERT_DIRECT_WT(SOC15_REG_OFFSET(UVD, i, mmUVD_RBC_RB_CNTL), tmp);

			ring = &adev->uvd.inst[i].ring_enc[0];
			ring->wptr = 0;
			MMSCH_V1_0_INSERT_DIRECT_WT(SOC15_REG_OFFSET(UVD, i, mmUVD_RB_BASE_LO), ring->gpu_addr);
			MMSCH_V1_0_INSERT_DIRECT_WT(SOC15_REG_OFFSET(UVD, i, mmUVD_RB_BASE_HI), upper_32_bits(ring->gpu_addr));
			MMSCH_V1_0_INSERT_DIRECT_WT(SOC15_REG_OFFSET(UVD, i, mmUVD_RB_SIZE), ring->ring_size / 4);

			/* boot up the VCPU */
			MMSCH_V1_0_INSERT_DIRECT_WT(SOC15_REG_OFFSET(UVD, i, mmUVD_SOFT_RESET), 0);

			/* enable UMC */
			MMSCH_V1_0_INSERT_DIRECT_RD_MOD_WT(SOC15_REG_OFFSET(UVD, i, mmUVD_LMI_CTRL2),
											   ~UVD_LMI_CTRL2__STALL_ARB_UMC_MASK, 0);

			MMSCH_V1_0_INSERT_DIRECT_POLL(SOC15_REG_OFFSET(UVD, i, mmUVD_STATUS), 0x02, 0x02);
		}
		/* add end packet */
		memcpy((void *)init_table, &end, sizeof(struct mmsch_v1_0_cmd_end));
		table_size += sizeof(struct mmsch_v1_0_cmd_end) / 4;
		header->uvd_table_size = table_size;

	}
	return uvd_v7_0_mmsch_start(adev, &adev->virt.mm_table);
}