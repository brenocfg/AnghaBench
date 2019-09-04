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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int DEV_UNKNOWN ; 
 int DEV_X16 ; 
 int DEV_X4 ; 
 int DEV_X8 ; 
 int GET_BITFIELD (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int get_width(u32 mtr)
{
	switch (GET_BITFIELD(mtr, 8, 9)) {
	case 0:
		return DEV_X4;
	case 1:
		return DEV_X8;
	case 2:
		return DEV_X16;
	}
	return DEV_UNKNOWN;
}