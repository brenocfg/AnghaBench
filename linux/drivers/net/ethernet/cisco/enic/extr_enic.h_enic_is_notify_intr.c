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
struct enic {int /*<<< orphan*/  vdev; } ;

/* Variables and functions */
#define  VNIC_DEV_INTR_MODE_INTX 130 
#define  VNIC_DEV_INTR_MODE_MSI 129 
#define  VNIC_DEV_INTR_MODE_MSIX 128 
 int enic_legacy_notify_intr () ; 
 int enic_msix_notify_intr (struct enic*) ; 
 int vnic_dev_get_intr_mode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool enic_is_notify_intr(struct enic *enic, int intr)
{
	switch (vnic_dev_get_intr_mode(enic->vdev)) {
	case VNIC_DEV_INTR_MODE_INTX:
		return intr == enic_legacy_notify_intr();
	case VNIC_DEV_INTR_MODE_MSIX:
		return intr == enic_msix_notify_intr(enic);
	case VNIC_DEV_INTR_MODE_MSI:
	default:
		return false;
	}
}