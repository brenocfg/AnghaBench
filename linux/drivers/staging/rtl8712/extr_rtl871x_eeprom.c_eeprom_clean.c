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
 int /*<<< orphan*/  EE_9346CR ; 
 int _EECS ; 
 int _EEDI ; 
 int /*<<< orphan*/  down_clk (struct _adapter*,int*) ; 
 int r8712_read8 (struct _adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8712_write8 (struct _adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_clk (struct _adapter*,int*) ; 

__attribute__((used)) static void eeprom_clean(struct _adapter *padapter)
{
	u16 x;

	if (padapter->surprise_removed)
		return;
	x = r8712_read8(padapter, EE_9346CR);
	if (padapter->surprise_removed)
		return;
	x &= ~(_EECS | _EEDI);
	r8712_write8(padapter, EE_9346CR, (u8)x);
	if (padapter->surprise_removed)
		return;
	up_clk(padapter, &x);
	if (padapter->surprise_removed)
		return;
	down_clk(padapter, &x);
}