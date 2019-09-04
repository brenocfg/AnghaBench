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
 int /*<<< orphan*/  CONFIG_64BIT ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u16 align_sp(unsigned int num)
{
	/* Double word alignment for 32-bit, quadword for 64-bit */
	unsigned int align = IS_ENABLED(CONFIG_64BIT) ? 16 : 8;
	num = (num + (align - 1)) & -align;
	return num;
}