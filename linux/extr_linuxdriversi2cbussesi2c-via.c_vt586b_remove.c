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
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_DIR ; 
 int /*<<< orphan*/  IOSPACE ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 scalar_t__ pm_io_base ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vt586b_adapter ; 

__attribute__((used)) static void vt586b_remove(struct pci_dev *dev)
{
	i2c_del_adapter(&vt586b_adapter);
	release_region(I2C_DIR, IOSPACE);
	pm_io_base = 0;
}