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
struct stm_fs {int ndiv; } ;

/* Variables and functions */

__attribute__((used)) static int clk_fs660c32_vco_get_rate(unsigned long input, struct stm_fs *fs,
			   unsigned long *rate)
{
	unsigned long nd = fs->ndiv + 16; /* ndiv value */

	*rate = input * nd;

	return 0;
}