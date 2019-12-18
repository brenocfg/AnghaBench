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
struct TYPE_2__ {int nvecs; int /*<<< orphan*/ * handler; } ;
struct bfa_s {TYPE_1__ msix; } ;

/* Variables and functions */
 int BFI_MSIX_CPE_QMAX_CB ; 
 int BFI_MSIX_CPE_QMIN_CB ; 
 int BFI_MSIX_RME_QMAX_CB ; 
 int BFI_MSIX_RME_QMIN_CB ; 
 int /*<<< orphan*/  bfa_msix_all ; 
 int /*<<< orphan*/  bfa_msix_reqq ; 
 int /*<<< orphan*/  bfa_msix_rspq ; 

void
bfa_hwcb_msix_queue_install(struct bfa_s *bfa)
{
	int i;

	if (bfa->msix.nvecs == 0)
		return;

	if (bfa->msix.nvecs == 1) {
		for (i = BFI_MSIX_CPE_QMIN_CB; i <= BFI_MSIX_RME_QMAX_CB; i++)
			bfa->msix.handler[i] = bfa_msix_all;
		return;
	}

	for (i = BFI_MSIX_CPE_QMIN_CB; i <= BFI_MSIX_CPE_QMAX_CB; i++)
		bfa->msix.handler[i] = bfa_msix_reqq;

	for (i = BFI_MSIX_RME_QMIN_CB; i <= BFI_MSIX_RME_QMAX_CB; i++)
		bfa->msix.handler[i] = bfa_msix_rspq;
}