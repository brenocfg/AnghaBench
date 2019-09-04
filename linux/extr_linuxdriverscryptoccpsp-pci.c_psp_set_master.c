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
struct sp_device {int dummy; } ;

/* Variables and functions */
 struct sp_device* sp_dev_master ; 
 scalar_t__ sp_pci_is_master (struct sp_device*) ; 

__attribute__((used)) static void psp_set_master(struct sp_device *sp)
{
	if (!sp_dev_master) {
		sp_dev_master = sp;
		return;
	}

	if (sp_pci_is_master(sp))
		sp_dev_master = sp;
}