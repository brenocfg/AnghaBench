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
struct _adapter {scalar_t__ surprise_removed; } ;

/* Variables and functions */
 int /*<<< orphan*/  EE_9346CR ; 
 int _EEDI ; 
 int _EEDO ; 
 int /*<<< orphan*/  down_clk (struct _adapter*,int*) ; 
 int r8712_read8 (struct _adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_clk (struct _adapter*,int*) ; 

__attribute__((used)) static u16 shift_in_bits(struct _adapter *padapter)
{
	u16 x, d = 0, i;

	if (padapter->surprise_removed)
		goto out;
	x = r8712_read8(padapter, EE_9346CR);
	x &= ~(_EEDO | _EEDI);
	d = 0;
	for (i = 0; i < 16; i++) {
		d <<= 1;
		up_clk(padapter, &x);
		if (padapter->surprise_removed)
			goto out;
		x = r8712_read8(padapter, EE_9346CR);
		x &= ~(_EEDI);
		if (x & _EEDO)
			d |= 1;
		down_clk(padapter, &x);
	}
out:
	return d;
}