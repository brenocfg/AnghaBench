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
struct gart_device {int dummy; } ;

/* Variables and functions */
 int GART_ENTRY_PHYS_ADDR_VALID ; 
 int gart_read_pte (struct gart_device*,unsigned long) ; 

__attribute__((used)) static inline bool gart_pte_valid(struct gart_device *gart, unsigned long iova)
{
	return !!(gart_read_pte(gart, iova) & GART_ENTRY_PHYS_ADDR_VALID);
}