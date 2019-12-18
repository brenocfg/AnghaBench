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

/* Variables and functions */
 int BIT6 ; 
 int BIT7 ; 
 int /*<<< orphan*/  CR6A ; 
 int /*<<< orphan*/  VIACR ; 
 int /*<<< orphan*/  viafb_write_reg_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void enable_second_display_channel(void)
{
	/* to enable second display channel. */
	viafb_write_reg_mask(CR6A, VIACR, 0x00, BIT6);
	viafb_write_reg_mask(CR6A, VIACR, BIT7, BIT7);
	viafb_write_reg_mask(CR6A, VIACR, BIT6, BIT6);
}