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
typedef  int u64 ;
struct cxl_afu {int /*<<< orphan*/  dev; TYPE_1__* guest; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  CXL_AFU_ERR_An ; 
 int /*<<< orphan*/  CXL_PSL_DSISR_An ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  cxl_afu_decode_psl_serr (struct cxl_afu*,int) ; 
 int cxl_h_ack_fn_error_interrupt (int /*<<< orphan*/ ,int) ; 
 int cxl_h_get_fn_error_interrupt (int /*<<< orphan*/ ,int*) ; 
 int cxl_p2n_read (struct cxl_afu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_crit (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static irqreturn_t guest_slice_irq_err(int irq, void *data)
{
	struct cxl_afu *afu = data;
	int rc;
	u64 serr, afu_error, dsisr;

	rc = cxl_h_get_fn_error_interrupt(afu->guest->handle, &serr);
	if (rc) {
		dev_crit(&afu->dev, "Couldn't read PSL_SERR_An: %d\n", rc);
		return IRQ_HANDLED;
	}
	afu_error = cxl_p2n_read(afu, CXL_AFU_ERR_An);
	dsisr = cxl_p2n_read(afu, CXL_PSL_DSISR_An);
	cxl_afu_decode_psl_serr(afu, serr);
	dev_crit(&afu->dev, "AFU_ERR_An: 0x%.16llx\n", afu_error);
	dev_crit(&afu->dev, "PSL_DSISR_An: 0x%.16llx\n", dsisr);

	rc = cxl_h_ack_fn_error_interrupt(afu->guest->handle, serr);
	if (rc)
		dev_crit(&afu->dev, "Couldn't ack slice error interrupt: %d\n",
			rc);

	return IRQ_HANDLED;
}