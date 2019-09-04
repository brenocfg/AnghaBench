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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ readl (scalar_t__) ; 
 scalar_t__ rt2880_pci_base ; 

__attribute__((used)) static u32 rt2880_pci_reg_read(u32 reg)
{
	return readl(rt2880_pci_base + reg);
}