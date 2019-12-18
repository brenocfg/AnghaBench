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
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  SLMP_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  CALC_REGADDR () ; 
 scalar_t__ RegAddr ; 

__attribute__((used)) static u16 read_reg16(SLMP_INFO * info, unsigned char Addr)
{
	CALC_REGADDR();
	return *((u16 *)RegAddr);
}