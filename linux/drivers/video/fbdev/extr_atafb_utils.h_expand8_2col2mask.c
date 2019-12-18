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
typedef  int u32 ;

/* Variables and functions */
 int* four2long ; 

__attribute__((used)) static inline void expand8_2col2mask(u8 fg, u8 bg, u32 fgm[], u32 bgm[])
{
	fgm[0] = four2long[fg & 15] ^ (bgm[0] = four2long[bg & 15]);
#if BPL > 4
	fgm[1] = four2long[fg >> 4] ^ (bgm[1] = four2long[bg >> 4]);
#endif
}