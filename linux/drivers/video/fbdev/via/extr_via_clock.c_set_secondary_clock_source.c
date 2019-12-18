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
typedef  int /*<<< orphan*/  u8 ;
typedef  enum via_clksrc { ____Placeholder_via_clksrc } via_clksrc ;

/* Variables and functions */
 int /*<<< orphan*/  VIACR ; 
 int /*<<< orphan*/  set_clock_source_common (int,int) ; 
 int /*<<< orphan*/  via_write_reg_mask (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void set_secondary_clock_source(enum via_clksrc source, bool use_pll)
{
	u8 data = set_clock_source_common(source, use_pll);
	via_write_reg_mask(VIACR, 0x6C, data, 0x0F);
}