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
 int EINVAL ; 
 char map_to_seg7 (int /*<<< orphan*/ *,char) ; 
 unsigned int tx_7segled_num ; 
 int /*<<< orphan*/  tx_7segled_putc (unsigned int,char) ; 
 int /*<<< orphan*/  txx9_seg7map ; 

int txx9_7segled_putc(unsigned int pos, char c)
{
	if (pos >= tx_7segled_num)
		return -EINVAL;
	c = map_to_seg7(&txx9_seg7map, c);
	if (c < 0)
		return c;
	tx_7segled_putc(pos, c);
	return 0;
}