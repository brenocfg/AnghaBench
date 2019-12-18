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
struct intel_ntb_dev {int self_mmio; int hwerr_flags; } ;

/* Variables and functions */
 int GEN3_DB_MSIX_VECTOR_COUNT ; 
 int /*<<< orphan*/  GEN3_DB_MSIX_VECTOR_SHIFT ; 
 int /*<<< orphan*/  GEN3_DB_TOTAL_SHIFT ; 
 int GEN3_INTVEC_OFFSET ; 
 int NTB_HWERR_MSIX_VECTOR32_BAD ; 
 int /*<<< orphan*/  iowrite8 (int,int) ; 
 int ndev_init_isr (struct intel_ntb_dev*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gen3_init_isr(struct intel_ntb_dev *ndev)
{
	int i;

	/*
	 * The MSIX vectors and the interrupt status bits are not lined up
	 * on Skylake. By default the link status bit is bit 32, however it
	 * is by default MSIX vector0. We need to fixup to line them up.
	 * The vectors at reset is 1-32,0. We need to reprogram to 0-32.
	 */

	for (i = 0; i < GEN3_DB_MSIX_VECTOR_COUNT; i++)
		iowrite8(i, ndev->self_mmio + GEN3_INTVEC_OFFSET + i);

	/* move link status down one as workaround */
	if (ndev->hwerr_flags & NTB_HWERR_MSIX_VECTOR32_BAD) {
		iowrite8(GEN3_DB_MSIX_VECTOR_COUNT - 2,
			 ndev->self_mmio + GEN3_INTVEC_OFFSET +
			 (GEN3_DB_MSIX_VECTOR_COUNT - 1));
	}

	return ndev_init_isr(ndev, GEN3_DB_MSIX_VECTOR_COUNT,
			     GEN3_DB_MSIX_VECTOR_COUNT,
			     GEN3_DB_MSIX_VECTOR_SHIFT,
			     GEN3_DB_TOTAL_SHIFT);
}