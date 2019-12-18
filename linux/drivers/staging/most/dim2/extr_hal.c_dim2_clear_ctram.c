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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  dim2_clear_ctr (int) ; 

__attribute__((used)) static void dim2_clear_ctram(void)
{
	u32 ctr_addr;

	for (ctr_addr = 0; ctr_addr < 0x90; ctr_addr++)
		dim2_clear_ctr(ctr_addr);
}