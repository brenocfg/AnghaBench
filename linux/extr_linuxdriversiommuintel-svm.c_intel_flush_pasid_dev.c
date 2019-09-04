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
struct qi_desc {int low; scalar_t__ high; } ;
struct intel_svm_dev {int /*<<< orphan*/  did; } ;
struct intel_svm {int /*<<< orphan*/  iommu; } ;

/* Variables and functions */
 int QI_PC_DID (int /*<<< orphan*/ ) ; 
 int QI_PC_PASID (int) ; 
 int QI_PC_PASID_SEL ; 
 int QI_PC_TYPE ; 
 int /*<<< orphan*/  qi_submit_sync (struct qi_desc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_flush_pasid_dev(struct intel_svm *svm, struct intel_svm_dev *sdev, int pasid)
{
	struct qi_desc desc;

	desc.high = 0;
	desc.low = QI_PC_TYPE | QI_PC_DID(sdev->did) | QI_PC_PASID_SEL | QI_PC_PASID(pasid);

	qi_submit_sync(&desc, svm->iommu);
}