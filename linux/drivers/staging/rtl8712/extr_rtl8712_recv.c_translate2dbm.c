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
struct _adapter {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */

__attribute__((used)) static s32  translate2dbm(struct _adapter *padapter, u8 signal_strength_idx)
{
	s32 signal_power; /* in dBm.*/
	/* Translate to dBm (x=0.5y-95).*/
	signal_power = (s32)((signal_strength_idx + 1) >> 1);
	signal_power -= 95;
	return signal_power;
}