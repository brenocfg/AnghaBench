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
typedef  int /*<<< orphan*/  u64 ;
struct pasid_entry {int /*<<< orphan*/ * val; } ;

/* Variables and functions */
 int /*<<< orphan*/  VTD_PAGE_MASK ; 
 int /*<<< orphan*/  pasid_set_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
pasid_set_flptr(struct pasid_entry *pe, u64 value)
{
	pasid_set_bits(&pe->val[2], VTD_PAGE_MASK, value);
}