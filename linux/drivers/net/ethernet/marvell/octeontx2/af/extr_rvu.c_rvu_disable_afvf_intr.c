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
struct rvu {int vfs; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTR_MASK (int) ; 
 int /*<<< orphan*/  RVU_PF_VFFLR_INT_ENA_W1CX (int) ; 
 int /*<<< orphan*/  RVU_PF_VFME_INT_ENA_W1CX (int) ; 
 int /*<<< orphan*/  RVU_PF_VFPF_MBOX_INT_ENA_W1CX (int) ; 
 int /*<<< orphan*/  rvupf_write64 (struct rvu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rvu_disable_afvf_intr(struct rvu *rvu)
{
	int vfs = rvu->vfs;

	rvupf_write64(rvu, RVU_PF_VFPF_MBOX_INT_ENA_W1CX(0), INTR_MASK(vfs));
	rvupf_write64(rvu, RVU_PF_VFFLR_INT_ENA_W1CX(0), INTR_MASK(vfs));
	rvupf_write64(rvu, RVU_PF_VFME_INT_ENA_W1CX(0), INTR_MASK(vfs));
	if (vfs <= 64)
		return;

	rvupf_write64(rvu, RVU_PF_VFPF_MBOX_INT_ENA_W1CX(1),
		      INTR_MASK(vfs - 64));
	rvupf_write64(rvu, RVU_PF_VFFLR_INT_ENA_W1CX(1), INTR_MASK(vfs - 64));
	rvupf_write64(rvu, RVU_PF_VFME_INT_ENA_W1CX(1), INTR_MASK(vfs - 64));
}