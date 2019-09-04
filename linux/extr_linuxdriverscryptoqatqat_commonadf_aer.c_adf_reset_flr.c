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
struct adf_accel_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  accel_to_pci_dev (struct adf_accel_dev*) ; 
 int /*<<< orphan*/  pcie_flr (int /*<<< orphan*/ ) ; 

void adf_reset_flr(struct adf_accel_dev *accel_dev)
{
	pcie_flr(accel_to_pci_dev(accel_dev));
}