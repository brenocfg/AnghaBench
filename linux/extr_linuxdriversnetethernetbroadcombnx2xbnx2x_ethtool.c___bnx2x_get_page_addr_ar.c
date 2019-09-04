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
typedef  int /*<<< orphan*/  u32 ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 scalar_t__ CHIP_IS_E2 (struct bnx2x*) ; 
 scalar_t__ CHIP_IS_E3 (struct bnx2x*) ; 
 int /*<<< orphan*/  const* page_vals_e2 ; 
 int /*<<< orphan*/  const* page_vals_e3 ; 

__attribute__((used)) static const u32 *__bnx2x_get_page_addr_ar(struct bnx2x *bp)
{
	if (CHIP_IS_E2(bp))
		return page_vals_e2;
	else if (CHIP_IS_E3(bp))
		return page_vals_e3;
	else
		return NULL;
}