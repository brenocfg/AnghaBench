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

/* Variables and functions */
 int /*<<< orphan*/  CR6A ; 
 int /*<<< orphan*/  CR91 ; 
 int** PowerSequenceOn ; 
 int /*<<< orphan*/  VIACR ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  viafb_write_reg_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void lcd_powersequence_on(void)
{
	int i, mask, data;

	/* Software control power sequence */
	viafb_write_reg_mask(CR91, VIACR, 0x11, 0x11);

	/* Enable LCD */
	viafb_write_reg_mask(CR6A, VIACR, 0x08, 0x08);

	for (i = 0; i < 3; i++) {
		mask = PowerSequenceOn[0][i];
		data = PowerSequenceOn[1][i] & mask;
		viafb_write_reg_mask(CR91, VIACR, (u8) data, (u8) mask);
		udelay(PowerSequenceOn[2][i]);
	}

	udelay(1);
}