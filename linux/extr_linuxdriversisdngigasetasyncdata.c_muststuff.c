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

/* Variables and functions */
 unsigned char PPP_ESCAPE ; 
 unsigned char PPP_FLAG ; 
 unsigned char PPP_TRANS ; 

__attribute__((used)) static inline int muststuff(unsigned char c)
{
	if (c < PPP_TRANS) return 1;
	if (c == PPP_FLAG) return 1;
	if (c == PPP_ESCAPE) return 1;
	/* other possible candidates: */
	/* 0x91: XON with parity set */
	/* 0x93: XOFF with parity set */
	return 0;
}