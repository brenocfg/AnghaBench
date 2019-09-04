#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct qcom_scm_desc {int arginfo; scalar_t__* args; } ;
struct device {int dummy; } ;
struct arm_smccc_res {scalar_t__ a0; } ;
struct TYPE_2__ {scalar_t__ a6; } ;
struct arm_smccc_quirk {TYPE_1__ state; int /*<<< orphan*/  id; } ;
typedef  scalar_t__ dma_addr_t ;
typedef  int /*<<< orphan*/  __le64 ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 scalar_t__ ARM_SMCCC_CALL_VAL (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ARM_SMCCC_OWNER_SIP ; 
 int /*<<< orphan*/  ARM_SMCCC_QUIRK_QCOM_A6 ; 
 scalar_t__ ARM_SMCCC_SMC_32 ; 
 int /*<<< orphan*/  ARM_SMCCC_STD_CALL ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENOMEM ; 
 size_t FIRST_EXT_ARG_IDX ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int N_EXT_QCOM_SCM_ARGS ; 
 int N_REGISTER_ARGS ; 
 int /*<<< orphan*/  PAGE_ALIGN (size_t) ; 
 int /*<<< orphan*/  QCOM_SCM_EBUSY_MAX_RETRY ; 
 int /*<<< orphan*/  QCOM_SCM_EBUSY_WAIT_MS ; 
 int /*<<< orphan*/  QCOM_SCM_FNID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ QCOM_SCM_INTERRUPTED ; 
 scalar_t__ QCOM_SCM_V2_EBUSY ; 
 int /*<<< orphan*/  arm_smccc_smc_quirk (scalar_t__,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,struct arm_smccc_res*,struct arm_smccc_quirk*) ; 
 int /*<<< orphan*/  cpu_to_le32 (scalar_t__) ; 
 int /*<<< orphan*/  cpu_to_le64 (scalar_t__) ; 
 scalar_t__ dma_map_single (struct device*,void*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,scalar_t__) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,scalar_t__,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qcom_scm_lock ; 
 int qcom_scm_remap_error (scalar_t__) ; 
 scalar_t__ qcom_smccc_convention ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int qcom_scm_call(struct device *dev, u32 svc_id, u32 cmd_id,
			 const struct qcom_scm_desc *desc,
			 struct arm_smccc_res *res)
{
	int arglen = desc->arginfo & 0xf;
	int retry_count = 0, i;
	u32 fn_id = QCOM_SCM_FNID(svc_id, cmd_id);
	u64 cmd, x5 = desc->args[FIRST_EXT_ARG_IDX];
	dma_addr_t args_phys = 0;
	void *args_virt = NULL;
	size_t alloc_len;
	struct arm_smccc_quirk quirk = {.id = ARM_SMCCC_QUIRK_QCOM_A6};

	if (unlikely(arglen > N_REGISTER_ARGS)) {
		alloc_len = N_EXT_QCOM_SCM_ARGS * sizeof(u64);
		args_virt = kzalloc(PAGE_ALIGN(alloc_len), GFP_KERNEL);

		if (!args_virt)
			return -ENOMEM;

		if (qcom_smccc_convention == ARM_SMCCC_SMC_32) {
			__le32 *args = args_virt;

			for (i = 0; i < N_EXT_QCOM_SCM_ARGS; i++)
				args[i] = cpu_to_le32(desc->args[i +
						      FIRST_EXT_ARG_IDX]);
		} else {
			__le64 *args = args_virt;

			for (i = 0; i < N_EXT_QCOM_SCM_ARGS; i++)
				args[i] = cpu_to_le64(desc->args[i +
						      FIRST_EXT_ARG_IDX]);
		}

		args_phys = dma_map_single(dev, args_virt, alloc_len,
					   DMA_TO_DEVICE);

		if (dma_mapping_error(dev, args_phys)) {
			kfree(args_virt);
			return -ENOMEM;
		}

		x5 = args_phys;
	}

	do {
		mutex_lock(&qcom_scm_lock);

		cmd = ARM_SMCCC_CALL_VAL(ARM_SMCCC_STD_CALL,
					 qcom_smccc_convention,
					 ARM_SMCCC_OWNER_SIP, fn_id);

		quirk.state.a6 = 0;

		do {
			arm_smccc_smc_quirk(cmd, desc->arginfo, desc->args[0],
				      desc->args[1], desc->args[2], x5,
				      quirk.state.a6, 0, res, &quirk);

			if (res->a0 == QCOM_SCM_INTERRUPTED)
				cmd = res->a0;

		} while (res->a0 == QCOM_SCM_INTERRUPTED);

		mutex_unlock(&qcom_scm_lock);

		if (res->a0 == QCOM_SCM_V2_EBUSY) {
			if (retry_count++ > QCOM_SCM_EBUSY_MAX_RETRY)
				break;
			msleep(QCOM_SCM_EBUSY_WAIT_MS);
		}
	}  while (res->a0 == QCOM_SCM_V2_EBUSY);

	if (args_virt) {
		dma_unmap_single(dev, args_phys, alloc_len, DMA_TO_DEVICE);
		kfree(args_virt);
	}

	if (res->a0 < 0)
		return qcom_scm_remap_error(res->a0);

	return 0;
}