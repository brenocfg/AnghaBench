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
typedef  int u64 ;
typedef  int u32 ;

/* Variables and functions */
 int GEN8_PML4E_MASK ; 
 int GEN8_PML4E_SHIFT ; 

__attribute__((used)) static inline u32 gen8_pml4e_index(u64 address)
{
	return (address >> GEN8_PML4E_SHIFT) & GEN8_PML4E_MASK;
}