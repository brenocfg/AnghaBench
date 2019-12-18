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
 scalar_t__ MT_PCIE_REMAP_BASE_1 ; 
 int MT_WTBL2_SIZE ; 

__attribute__((used)) static u32
mt7603_wtbl2_addr(int idx)
{
	/* Mapped to WTBL2 */
	return MT_PCIE_REMAP_BASE_1 + idx * MT_WTBL2_SIZE;
}