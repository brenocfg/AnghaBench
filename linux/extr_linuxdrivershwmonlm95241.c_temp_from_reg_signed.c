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
typedef  int u8 ;
typedef  int s16 ;

/* Variables and functions */

__attribute__((used)) static int temp_from_reg_signed(u8 val_h, u8 val_l)
{
	s16 val_hl = (val_h << 8) | val_l;
	return val_hl * 1000 / 256;
}