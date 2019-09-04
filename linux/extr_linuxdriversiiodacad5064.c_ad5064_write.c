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
struct ad5064_state {int (* write ) (struct ad5064_state*,unsigned int,unsigned int,unsigned int) ;} ;

/* Variables and functions */
 int stub1 (struct ad5064_state*,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static int ad5064_write(struct ad5064_state *st, unsigned int cmd,
	unsigned int addr, unsigned int val, unsigned int shift)
{
	val <<= shift;

	return st->write(st, cmd, addr, val);
}