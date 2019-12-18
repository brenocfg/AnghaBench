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

/* Variables and functions */
 int pci_register_driver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vrc4173_cardu_driver ; 
 scalar_t__ vrc4173_cardu_slots ; 

__attribute__((used)) static int vrc4173_cardu_init(void)
{
	vrc4173_cardu_slots = 0;

	return pci_register_driver(&vrc4173_cardu_driver);
}