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
struct bfa_ioc {TYPE_1__* attr; } ;
struct TYPE_2__ {char asic_rev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_IOC_CHIP_REV_LEN ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_ioc_get_pci_chip_rev(struct bfa_ioc *ioc, char *chip_rev)
{
	BUG_ON(!(chip_rev));

	memset(chip_rev, 0, BFA_IOC_CHIP_REV_LEN);

	chip_rev[0] = 'R';
	chip_rev[1] = 'e';
	chip_rev[2] = 'v';
	chip_rev[3] = '-';
	chip_rev[4] = ioc->attr->asic_rev;
	chip_rev[5] = '\0';
}