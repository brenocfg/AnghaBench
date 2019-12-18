#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ad7606_state {TYPE_1__* bops; } ;
struct TYPE_2__ {int (* reg_read ) (struct ad7606_state*,unsigned int) ;int (* reg_write ) (struct ad7606_state*,unsigned int,int) ;} ;

/* Variables and functions */
 int stub1 (struct ad7606_state*,unsigned int) ; 
 int stub2 (struct ad7606_state*,unsigned int,int) ; 

__attribute__((used)) static int ad7606_spi_write_mask(struct ad7606_state *st,
				 unsigned int addr,
				 unsigned long mask,
				 unsigned int val)
{
	int readval;

	readval = st->bops->reg_read(st, addr);
	if (readval < 0)
		return readval;

	readval &= ~mask;
	readval |= val;

	return st->bops->reg_write(st, addr, readval);
}