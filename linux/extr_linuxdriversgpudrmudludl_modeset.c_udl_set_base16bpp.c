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
typedef  int u32 ;

/* Variables and functions */
 char* udl_set_register (char*,int,int) ; 

__attribute__((used)) static char *udl_set_base16bpp(char *wrptr, u32 base)
{
	/* the base pointer is 16 bits wide, 0x20 is hi byte. */
	wrptr = udl_set_register(wrptr, 0x20, base >> 16);
	wrptr = udl_set_register(wrptr, 0x21, base >> 8);
	return udl_set_register(wrptr, 0x22, base);
}