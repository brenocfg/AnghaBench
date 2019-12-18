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
typedef  unsigned long const s32 ;
typedef  unsigned long __u8 ;

/* Variables and functions */

__attribute__((used)) static s32 uclogic_params_get_le24(const void *p)
{
	const __u8 *b = p;
	return b[0] | (b[1] << 8UL) | (b[2] << 16UL);
}