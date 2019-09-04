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
typedef  int u16 ;
struct radeon_device {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int ffs (int) ; 
 int pcie_get_readrq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcie_set_readrq (int /*<<< orphan*/ ,int) ; 

void evergreen_fix_pci_max_read_req_size(struct radeon_device *rdev)
{
	int readrq;
	u16 v;

	readrq = pcie_get_readrq(rdev->pdev);
	v = ffs(readrq) - 8;
	/* if bios or OS sets MAX_READ_REQUEST_SIZE to an invalid value, fix it
	 * to avoid hangs or perfomance issues
	 */
	if ((v == 0) || (v == 6) || (v == 7))
		pcie_set_readrq(rdev->pdev, 512);
}