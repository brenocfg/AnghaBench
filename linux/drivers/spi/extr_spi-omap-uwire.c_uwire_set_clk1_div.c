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
typedef  int u16 ;

/* Variables and functions */
 int /*<<< orphan*/  UWIRE_SR3 ; 
 int uwire_read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uwire_write_reg (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void uwire_set_clk1_div(int div1_idx)
{
	u16 w;

	w = uwire_read_reg(UWIRE_SR3);
	w &= ~(0x03 << 1);
	w |= div1_idx << 1;
	uwire_write_reg(UWIRE_SR3, w);
}