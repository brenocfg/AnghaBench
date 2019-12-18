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
typedef  int u16 ;
struct _adapter {scalar_t__ surprise_removed; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_RATE ; 
 int /*<<< orphan*/  EE_9346CR ; 
 int _EEDI ; 
 int _EEDO ; 
 int /*<<< orphan*/  down_clk (struct _adapter*,int*) ; 
 int r8712_read8 (struct _adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8712_write8 (struct _adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_clk (struct _adapter*,int*) ; 

__attribute__((used)) static void shift_out_bits(struct _adapter *padapter, u16 data, u16 count)
{
	u16 x, mask;

	if (padapter->surprise_removed)
		goto out;
	mask = 0x01 << (count - 1);
	x = r8712_read8(padapter, EE_9346CR);
	x &= ~(_EEDO | _EEDI);
	do {
		x &= ~_EEDI;
		if (data & mask)
			x |= _EEDI;
		if (padapter->surprise_removed)
			goto out;
		r8712_write8(padapter, EE_9346CR, (u8)x);
		udelay(CLOCK_RATE);
		up_clk(padapter, &x);
		down_clk(padapter, &x);
		mask >>= 1;
	} while (mask);
	if (padapter->surprise_removed)
		goto out;
	x &= ~_EEDI;
	r8712_write8(padapter, EE_9346CR, (u8)x);
out:;
}