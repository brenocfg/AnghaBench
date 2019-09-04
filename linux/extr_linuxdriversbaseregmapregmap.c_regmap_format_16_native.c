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
typedef  unsigned int u16 ;

/* Variables and functions */

__attribute__((used)) static void regmap_format_16_native(void *buf, unsigned int val,
				    unsigned int shift)
{
	*(u16 *)buf = val << shift;
}