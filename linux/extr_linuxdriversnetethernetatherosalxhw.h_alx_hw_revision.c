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
struct alx_hw {TYPE_1__* pdev; } ;
struct TYPE_2__ {int revision; } ;

/* Variables and functions */
 int ALX_PCI_REVID_SHIFT ; 

__attribute__((used)) static inline int alx_hw_revision(struct alx_hw *hw)
{
	return hw->pdev->revision >> ALX_PCI_REVID_SHIFT;
}