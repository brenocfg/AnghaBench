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
struct TYPE_2__ {int /*<<< orphan*/ * base; } ;
struct rt2x00_dev {TYPE_1__ csr; int /*<<< orphan*/ * eeprom; int /*<<< orphan*/ * rf; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rt2x00pci_free_reg(struct rt2x00_dev *rt2x00dev)
{
	kfree(rt2x00dev->rf);
	rt2x00dev->rf = NULL;

	kfree(rt2x00dev->eeprom);
	rt2x00dev->eeprom = NULL;

	if (rt2x00dev->csr.base) {
		iounmap(rt2x00dev->csr.base);
		rt2x00dev->csr.base = NULL;
	}
}