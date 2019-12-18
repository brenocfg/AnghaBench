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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 scalar_t__ CDT ; 
 int /*<<< orphan*/  dim2_write_ctr (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dim2_clear_cdt(u8 ch_addr)
{
	u32 cdt[4] = { 0, 0, 0, 0 };

	dim2_write_ctr(CDT + ch_addr, cdt);
}