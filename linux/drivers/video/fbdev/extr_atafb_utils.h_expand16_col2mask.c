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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/ * two2word ; 

__attribute__((used)) static inline void expand16_col2mask(u8 c, u32 m[])
{
	m[0] = two2word[c & 3];
#if BPL > 2
	m[1] = two2word[(c >> 2) & 3];
#endif
#if BPL > 4
	m[2] = two2word[(c >> 4) & 3];
	m[3] = two2word[c >> 6];
#endif
}