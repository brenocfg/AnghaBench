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
struct nvt_dev {int /*<<< orphan*/  cr_efir; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  EFER_EFM_ENABLE ; 
 int /*<<< orphan*/  NVT_DRIVER_NAME ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  request_muxed_region (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int nvt_efm_enable(struct nvt_dev *nvt)
{
	if (!request_muxed_region(nvt->cr_efir, 2, NVT_DRIVER_NAME))
		return -EBUSY;

	/* Enabling Extended Function Mode explicitly requires writing 2x */
	outb(EFER_EFM_ENABLE, nvt->cr_efir);
	outb(EFER_EFM_ENABLE, nvt->cr_efir);

	return 0;
}