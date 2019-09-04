#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct fman {TYPE_4__* fpm_regs; TYPE_3__* bmi_regs; TYPE_2__* qmi_regs; TYPE_1__* dma_regs; } ;
typedef  enum fman_exceptions { ____Placeholder_fman_exceptions } fman_exceptions ;
struct TYPE_9__ {int /*<<< orphan*/  fm_rie; int /*<<< orphan*/  fmfp_ee; } ;
struct TYPE_8__ {int /*<<< orphan*/  fmbm_ier; } ;
struct TYPE_7__ {int /*<<< orphan*/  fmqm_eien; int /*<<< orphan*/  fmqm_ien; } ;
struct TYPE_6__ {int /*<<< orphan*/  fmdmmr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMI_ERR_INTR_EN_DISPATCH_RAM_ECC ; 
 int /*<<< orphan*/  BMI_ERR_INTR_EN_LIST_RAM_ECC ; 
 int /*<<< orphan*/  BMI_ERR_INTR_EN_STATISTICS_RAM_ECC ; 
 int /*<<< orphan*/  BMI_ERR_INTR_EN_STORAGE_PROFILE_ECC ; 
 int /*<<< orphan*/  DMA_MODE_BER ; 
 int /*<<< orphan*/  DMA_MODE_ECC ; 
 int EINVAL ; 
#define  FMAN_EX_BMI_DISPATCH_RAM_ECC 143 
#define  FMAN_EX_BMI_LIST_RAM_ECC 142 
#define  FMAN_EX_BMI_STATISTICS_RAM_ECC 141 
#define  FMAN_EX_BMI_STORAGE_PROFILE_ECC 140 
#define  FMAN_EX_DMA_BUS_ERROR 139 
#define  FMAN_EX_DMA_FM_WRITE_ECC 138 
#define  FMAN_EX_DMA_READ_ECC 137 
#define  FMAN_EX_DMA_SYSTEM_WRITE_ECC 136 
#define  FMAN_EX_FPM_DOUBLE_ECC 135 
#define  FMAN_EX_FPM_SINGLE_ECC 134 
#define  FMAN_EX_FPM_STALL_ON_TASKS 133 
#define  FMAN_EX_IRAM_ECC 132 
#define  FMAN_EX_MURAM_ECC 131 
#define  FMAN_EX_QMI_DEQ_FROM_UNKNOWN_PORTID 130 
#define  FMAN_EX_QMI_DOUBLE_ECC 129 
#define  FMAN_EX_QMI_SINGLE_ECC 128 
 int /*<<< orphan*/  FPM_EV_MASK_DOUBLE_ECC_EN ; 
 int /*<<< orphan*/  FPM_EV_MASK_SINGLE_ECC_EN ; 
 int /*<<< orphan*/  FPM_EV_MASK_STALL_EN ; 
 int /*<<< orphan*/  FPM_IRAM_ECC_ERR_EX_EN ; 
 int /*<<< orphan*/  FPM_MURAM_ECC_ERR_EX_EN ; 
 int /*<<< orphan*/  QMI_ERR_INTR_EN_DEQ_FROM_DEF ; 
 int /*<<< orphan*/  QMI_ERR_INTR_EN_DOUBLE_ECC ; 
 int /*<<< orphan*/  QMI_INTR_EN_SINGLE_ECC ; 
 int /*<<< orphan*/  disable_rams_ecc (TYPE_4__*) ; 
 int /*<<< orphan*/  enable_rams_ecc (TYPE_4__*) ; 
 int /*<<< orphan*/  ioread32be (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32be (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int set_exception(struct fman *fman,
			 enum fman_exceptions exception, bool enable)
{
	u32 tmp;

	switch (exception) {
	case FMAN_EX_DMA_BUS_ERROR:
		tmp = ioread32be(&fman->dma_regs->fmdmmr);
		if (enable)
			tmp |= DMA_MODE_BER;
		else
			tmp &= ~DMA_MODE_BER;
		/* disable bus error */
		iowrite32be(tmp, &fman->dma_regs->fmdmmr);
		break;
	case FMAN_EX_DMA_READ_ECC:
	case FMAN_EX_DMA_SYSTEM_WRITE_ECC:
	case FMAN_EX_DMA_FM_WRITE_ECC:
		tmp = ioread32be(&fman->dma_regs->fmdmmr);
		if (enable)
			tmp |= DMA_MODE_ECC;
		else
			tmp &= ~DMA_MODE_ECC;
		iowrite32be(tmp, &fman->dma_regs->fmdmmr);
		break;
	case FMAN_EX_FPM_STALL_ON_TASKS:
		tmp = ioread32be(&fman->fpm_regs->fmfp_ee);
		if (enable)
			tmp |= FPM_EV_MASK_STALL_EN;
		else
			tmp &= ~FPM_EV_MASK_STALL_EN;
		iowrite32be(tmp, &fman->fpm_regs->fmfp_ee);
		break;
	case FMAN_EX_FPM_SINGLE_ECC:
		tmp = ioread32be(&fman->fpm_regs->fmfp_ee);
		if (enable)
			tmp |= FPM_EV_MASK_SINGLE_ECC_EN;
		else
			tmp &= ~FPM_EV_MASK_SINGLE_ECC_EN;
		iowrite32be(tmp, &fman->fpm_regs->fmfp_ee);
		break;
	case FMAN_EX_FPM_DOUBLE_ECC:
		tmp = ioread32be(&fman->fpm_regs->fmfp_ee);
		if (enable)
			tmp |= FPM_EV_MASK_DOUBLE_ECC_EN;
		else
			tmp &= ~FPM_EV_MASK_DOUBLE_ECC_EN;
		iowrite32be(tmp, &fman->fpm_regs->fmfp_ee);
		break;
	case FMAN_EX_QMI_SINGLE_ECC:
		tmp = ioread32be(&fman->qmi_regs->fmqm_ien);
		if (enable)
			tmp |= QMI_INTR_EN_SINGLE_ECC;
		else
			tmp &= ~QMI_INTR_EN_SINGLE_ECC;
		iowrite32be(tmp, &fman->qmi_regs->fmqm_ien);
		break;
	case FMAN_EX_QMI_DOUBLE_ECC:
		tmp = ioread32be(&fman->qmi_regs->fmqm_eien);
		if (enable)
			tmp |= QMI_ERR_INTR_EN_DOUBLE_ECC;
		else
			tmp &= ~QMI_ERR_INTR_EN_DOUBLE_ECC;
		iowrite32be(tmp, &fman->qmi_regs->fmqm_eien);
		break;
	case FMAN_EX_QMI_DEQ_FROM_UNKNOWN_PORTID:
		tmp = ioread32be(&fman->qmi_regs->fmqm_eien);
		if (enable)
			tmp |= QMI_ERR_INTR_EN_DEQ_FROM_DEF;
		else
			tmp &= ~QMI_ERR_INTR_EN_DEQ_FROM_DEF;
		iowrite32be(tmp, &fman->qmi_regs->fmqm_eien);
		break;
	case FMAN_EX_BMI_LIST_RAM_ECC:
		tmp = ioread32be(&fman->bmi_regs->fmbm_ier);
		if (enable)
			tmp |= BMI_ERR_INTR_EN_LIST_RAM_ECC;
		else
			tmp &= ~BMI_ERR_INTR_EN_LIST_RAM_ECC;
		iowrite32be(tmp, &fman->bmi_regs->fmbm_ier);
		break;
	case FMAN_EX_BMI_STORAGE_PROFILE_ECC:
		tmp = ioread32be(&fman->bmi_regs->fmbm_ier);
		if (enable)
			tmp |= BMI_ERR_INTR_EN_STORAGE_PROFILE_ECC;
		else
			tmp &= ~BMI_ERR_INTR_EN_STORAGE_PROFILE_ECC;
		iowrite32be(tmp, &fman->bmi_regs->fmbm_ier);
		break;
	case FMAN_EX_BMI_STATISTICS_RAM_ECC:
		tmp = ioread32be(&fman->bmi_regs->fmbm_ier);
		if (enable)
			tmp |= BMI_ERR_INTR_EN_STATISTICS_RAM_ECC;
		else
			tmp &= ~BMI_ERR_INTR_EN_STATISTICS_RAM_ECC;
		iowrite32be(tmp, &fman->bmi_regs->fmbm_ier);
		break;
	case FMAN_EX_BMI_DISPATCH_RAM_ECC:
		tmp = ioread32be(&fman->bmi_regs->fmbm_ier);
		if (enable)
			tmp |= BMI_ERR_INTR_EN_DISPATCH_RAM_ECC;
		else
			tmp &= ~BMI_ERR_INTR_EN_DISPATCH_RAM_ECC;
		iowrite32be(tmp, &fman->bmi_regs->fmbm_ier);
		break;
	case FMAN_EX_IRAM_ECC:
		tmp = ioread32be(&fman->fpm_regs->fm_rie);
		if (enable) {
			/* enable ECC if not enabled */
			enable_rams_ecc(fman->fpm_regs);
			/* enable ECC interrupts */
			tmp |= FPM_IRAM_ECC_ERR_EX_EN;
		} else {
			/* ECC mechanism may be disabled,
			 * depending on driver status
			 */
			disable_rams_ecc(fman->fpm_regs);
			tmp &= ~FPM_IRAM_ECC_ERR_EX_EN;
		}
		iowrite32be(tmp, &fman->fpm_regs->fm_rie);
		break;
	case FMAN_EX_MURAM_ECC:
		tmp = ioread32be(&fman->fpm_regs->fm_rie);
		if (enable) {
			/* enable ECC if not enabled */
			enable_rams_ecc(fman->fpm_regs);
			/* enable ECC interrupts */
			tmp |= FPM_MURAM_ECC_ERR_EX_EN;
		} else {
			/* ECC mechanism may be disabled,
			 * depending on driver status
			 */
			disable_rams_ecc(fman->fpm_regs);
			tmp &= ~FPM_MURAM_ECC_ERR_EX_EN;
		}
		iowrite32be(tmp, &fman->fpm_regs->fm_rie);
		break;
	default:
		return -EINVAL;
	}
	return 0;
}