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
struct odm_dm_struct {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */

__attribute__((used)) static s32 odm_signal_scale_mapping(struct odm_dm_struct *dm_odm, s32 currsig)
{
	s32 retsig = 0;

	if (currsig >= 51 && currsig <= 100)
		retsig = 100;
	else if (currsig >= 41 && currsig <= 50)
		retsig = 80 + ((currsig - 40) * 2);
	else if (currsig >= 31 && currsig <= 40)
		retsig = 66 + (currsig - 30);
	else if (currsig >= 21 && currsig <= 30)
		retsig = 54 + (currsig - 20);
	else if (currsig >= 10 && currsig <= 20)
		retsig = 42 + (((currsig - 10) * 2) / 3);
	else if (currsig >= 5 && currsig <= 9)
		retsig = 22 + (((currsig - 5) * 3) / 2);
	else if (currsig >= 1 && currsig <= 4)
		retsig = 6 + (((currsig - 1) * 3) / 2);
	else
		retsig = currsig;

	return retsig;
}