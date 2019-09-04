#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct cm3232_chip {int regs_cmd; } ;
struct TYPE_3__ {int it; int val; int val2; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int CM3232_CMD_ALS_IT_MASK ; 
 int CM3232_CMD_ALS_IT_SHIFT ; 
 int EINVAL ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 TYPE_1__* cm3232_als_it_scales ; 

__attribute__((used)) static int cm3232_read_als_it(struct cm3232_chip *chip, int *val, int *val2)
{
	u16 als_it;
	int i;

	als_it = chip->regs_cmd;
	als_it &= CM3232_CMD_ALS_IT_MASK;
	als_it >>= CM3232_CMD_ALS_IT_SHIFT;
	for (i = 0; i < ARRAY_SIZE(cm3232_als_it_scales); i++) {
		if (als_it == cm3232_als_it_scales[i].it) {
			*val = cm3232_als_it_scales[i].val;
			*val2 = cm3232_als_it_scales[i].val2;
			return IIO_VAL_INT_PLUS_MICRO;
		}
	}

	return -EINVAL;
}