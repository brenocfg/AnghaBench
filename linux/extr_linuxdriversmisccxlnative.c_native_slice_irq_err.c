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
typedef  int u64 ;
struct cxl_afu {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  CXL_AFU_DEBUG_An ; 
 int /*<<< orphan*/  CXL_AFU_ERR_An ; 
 int /*<<< orphan*/  CXL_PSL_DSISR_An ; 
 int /*<<< orphan*/  CXL_PSL_ErrStat_An ; 
 int /*<<< orphan*/  CXL_PSL_FIR_SLICE_An ; 
 int /*<<< orphan*/  CXL_PSL_SERR_An ; 
 int CXL_PSL_SERR_An_IRQS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  cxl_afu_decode_psl_serr (struct cxl_afu*,int) ; 
 scalar_t__ cxl_is_power8 () ; 
 int cxl_p1n_read (struct cxl_afu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxl_p1n_write (struct cxl_afu*,int /*<<< orphan*/ ,int) ; 
 int cxl_p2n_read (struct cxl_afu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_crit (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static irqreturn_t native_slice_irq_err(int irq, void *data)
{
	struct cxl_afu *afu = data;
	u64 errstat, serr, afu_error, dsisr;
	u64 fir_slice, afu_debug, irq_mask;

	/*
	 * slice err interrupt is only used with full PSL (no XSL)
	 */
	serr = cxl_p1n_read(afu, CXL_PSL_SERR_An);
	errstat = cxl_p2n_read(afu, CXL_PSL_ErrStat_An);
	afu_error = cxl_p2n_read(afu, CXL_AFU_ERR_An);
	dsisr = cxl_p2n_read(afu, CXL_PSL_DSISR_An);
	cxl_afu_decode_psl_serr(afu, serr);

	if (cxl_is_power8()) {
		fir_slice = cxl_p1n_read(afu, CXL_PSL_FIR_SLICE_An);
		afu_debug = cxl_p1n_read(afu, CXL_AFU_DEBUG_An);
		dev_crit(&afu->dev, "PSL_FIR_SLICE_An: 0x%016llx\n", fir_slice);
		dev_crit(&afu->dev, "CXL_PSL_AFU_DEBUG_An: 0x%016llx\n", afu_debug);
	}
	dev_crit(&afu->dev, "CXL_PSL_ErrStat_An: 0x%016llx\n", errstat);
	dev_crit(&afu->dev, "AFU_ERR_An: 0x%.16llx\n", afu_error);
	dev_crit(&afu->dev, "PSL_DSISR_An: 0x%.16llx\n", dsisr);

	/* mask off the IRQ so it won't retrigger until the AFU is reset */
	irq_mask = (serr & CXL_PSL_SERR_An_IRQS) >> 32;
	serr |= irq_mask;
	cxl_p1n_write(afu, CXL_PSL_SERR_An, serr);
	dev_info(&afu->dev, "Further such interrupts will be masked until the AFU is reset\n");

	return IRQ_HANDLED;
}