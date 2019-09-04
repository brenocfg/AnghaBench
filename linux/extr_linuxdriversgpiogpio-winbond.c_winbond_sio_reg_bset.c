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

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  winbond_sio_reg_read (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  winbond_sio_reg_write (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void winbond_sio_reg_bset(unsigned long base, u8 reg, u8 bit)
{
	u8 val;

	val = winbond_sio_reg_read(base, reg);
	val |= BIT(bit);
	winbond_sio_reg_write(base, reg, val);
}