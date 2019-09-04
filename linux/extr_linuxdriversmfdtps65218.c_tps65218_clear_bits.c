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
struct tps65218 {int dummy; } ;

/* Variables and functions */
 int tps65218_update_bits (struct tps65218*,unsigned int,unsigned int,int /*<<< orphan*/ ,unsigned int) ; 

int tps65218_clear_bits(struct tps65218 *tps, unsigned int reg,
		unsigned int mask, unsigned int level)
{
	return tps65218_update_bits(tps, reg, mask, 0, level);
}