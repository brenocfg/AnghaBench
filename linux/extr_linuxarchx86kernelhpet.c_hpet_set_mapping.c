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
 int /*<<< orphan*/  HPET_MMAP_SIZE ; 
 int /*<<< orphan*/  hpet_address ; 
 int /*<<< orphan*/  hpet_virt_address ; 
 int /*<<< orphan*/  ioremap_nocache (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void hpet_set_mapping(void)
{
	hpet_virt_address = ioremap_nocache(hpet_address, HPET_MMAP_SIZE);
}