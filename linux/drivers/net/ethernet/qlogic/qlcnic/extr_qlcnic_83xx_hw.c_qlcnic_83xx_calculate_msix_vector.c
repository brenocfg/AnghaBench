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
struct qlcnic_adapter {int drv_sds_rings; int flags; scalar_t__ drv_tx_rings; } ;

/* Variables and functions */
 int QLCNIC_TX_INTR_SHARED ; 

__attribute__((used)) static int qlcnic_83xx_calculate_msix_vector(struct qlcnic_adapter *adapter)
{
	int num_msix;

	num_msix = adapter->drv_sds_rings;

	/* account for AEN interrupt MSI-X based interrupts */
	num_msix += 1;

	if (!(adapter->flags & QLCNIC_TX_INTR_SHARED))
		num_msix += adapter->drv_tx_rings;

	return num_msix;
}