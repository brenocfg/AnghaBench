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
struct amdgpu_device {int /*<<< orphan*/  grbm_idx_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_TIMESTAMP ; 
 int /*<<< orphan*/  CU_ID ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  DRM_INFO (char*,...) ; 
 int /*<<< orphan*/  ENCODING ; 
 int /*<<< orphan*/  HOST_CMD_OVERFLOW ; 
 int /*<<< orphan*/  HOST_REG_OVERFLOW ; 
 int /*<<< orphan*/  IMMED_OVERFLOW ; 
 int /*<<< orphan*/  PRIV ; 
 int REG_GET_FIELD (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_TIMESTAMP ; 
 unsigned int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SE_ID ; 
 int /*<<< orphan*/  SH_ID ; 
 int /*<<< orphan*/  SIMD_ID ; 
 int /*<<< orphan*/  SOURCE ; 
 int /*<<< orphan*/  SQ_EDC_INFO ; 
 int /*<<< orphan*/  SQ_INTERRUPT_WORD_AUTO ; 
 int /*<<< orphan*/  SQ_INTERRUPT_WORD_CMN ; 
 int /*<<< orphan*/  SQ_INTERRUPT_WORD_WAVE ; 
 int /*<<< orphan*/  THREAD_TRACE ; 
 int /*<<< orphan*/  THREAD_TRACE_BUF_FULL ; 
 int /*<<< orphan*/  VM_ID ; 
 int /*<<< orphan*/  WAVE_ID ; 
 int /*<<< orphan*/  WLT ; 
 int /*<<< orphan*/  gfx_v8_0_select_se_sh (struct amdgpu_device*,int,int,int) ; 
 int /*<<< orphan*/  in_task () ; 
 int /*<<< orphan*/  mmSQ_EDC_INFO ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 
 char** sq_edc_source_names ; 

__attribute__((used)) static void gfx_v8_0_parse_sq_irq(struct amdgpu_device *adev, unsigned ih_data)
{
	u32 enc, se_id, sh_id, cu_id;
	char type[20];
	int sq_edc_source = -1;

	enc = REG_GET_FIELD(ih_data, SQ_INTERRUPT_WORD_CMN, ENCODING);
	se_id = REG_GET_FIELD(ih_data, SQ_INTERRUPT_WORD_CMN, SE_ID);

	switch (enc) {
		case 0:
			DRM_INFO("SQ general purpose intr detected:"
					"se_id %d, immed_overflow %d, host_reg_overflow %d,"
					"host_cmd_overflow %d, cmd_timestamp %d,"
					"reg_timestamp %d, thread_trace_buff_full %d,"
					"wlt %d, thread_trace %d.\n",
					se_id,
					REG_GET_FIELD(ih_data, SQ_INTERRUPT_WORD_AUTO, IMMED_OVERFLOW),
					REG_GET_FIELD(ih_data, SQ_INTERRUPT_WORD_AUTO, HOST_REG_OVERFLOW),
					REG_GET_FIELD(ih_data, SQ_INTERRUPT_WORD_AUTO, HOST_CMD_OVERFLOW),
					REG_GET_FIELD(ih_data, SQ_INTERRUPT_WORD_AUTO, CMD_TIMESTAMP),
					REG_GET_FIELD(ih_data, SQ_INTERRUPT_WORD_AUTO, REG_TIMESTAMP),
					REG_GET_FIELD(ih_data, SQ_INTERRUPT_WORD_AUTO, THREAD_TRACE_BUF_FULL),
					REG_GET_FIELD(ih_data, SQ_INTERRUPT_WORD_AUTO, WLT),
					REG_GET_FIELD(ih_data, SQ_INTERRUPT_WORD_AUTO, THREAD_TRACE)
					);
			break;
		case 1:
		case 2:

			cu_id = REG_GET_FIELD(ih_data, SQ_INTERRUPT_WORD_WAVE, CU_ID);
			sh_id = REG_GET_FIELD(ih_data, SQ_INTERRUPT_WORD_WAVE, SH_ID);

			/*
			 * This function can be called either directly from ISR
			 * or from BH in which case we can access SQ_EDC_INFO
			 * instance
			 */
			if (in_task()) {
				mutex_lock(&adev->grbm_idx_mutex);
				gfx_v8_0_select_se_sh(adev, se_id, sh_id, cu_id);

				sq_edc_source = REG_GET_FIELD(RREG32(mmSQ_EDC_INFO), SQ_EDC_INFO, SOURCE);

				gfx_v8_0_select_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff);
				mutex_unlock(&adev->grbm_idx_mutex);
			}

			if (enc == 1)
				sprintf(type, "instruction intr");
			else
				sprintf(type, "EDC/ECC error");

			DRM_INFO(
				"SQ %s detected: "
					"se_id %d, sh_id %d, cu_id %d, simd_id %d, wave_id %d, vm_id %d "
					"trap %s, sq_ed_info.source %s.\n",
					type, se_id, sh_id, cu_id,
					REG_GET_FIELD(ih_data, SQ_INTERRUPT_WORD_WAVE, SIMD_ID),
					REG_GET_FIELD(ih_data, SQ_INTERRUPT_WORD_WAVE, WAVE_ID),
					REG_GET_FIELD(ih_data, SQ_INTERRUPT_WORD_WAVE, VM_ID),
					REG_GET_FIELD(ih_data, SQ_INTERRUPT_WORD_WAVE, PRIV) ? "true" : "false",
					(sq_edc_source != -1) ? sq_edc_source_names[sq_edc_source] : "unavailable"
				);
			break;
		default:
			DRM_ERROR("SQ invalid encoding type\n.");
	}
}