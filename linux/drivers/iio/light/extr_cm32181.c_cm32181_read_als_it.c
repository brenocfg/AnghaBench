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
typedef  int u16 ;
struct cm32181_chip {int* conf_regs; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int CM32181_CMD_ALS_IT_MASK ; 
 int CM32181_CMD_ALS_IT_SHIFT ; 
 size_t CM32181_REG_ADDR_CMD ; 
 int EINVAL ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 int* als_it_bits ; 
 int* als_it_value ; 

__attribute__((used)) static int cm32181_read_als_it(struct cm32181_chip *cm32181, int *val2)
{
	u16 als_it;
	int i;

	als_it = cm32181->conf_regs[CM32181_REG_ADDR_CMD];
	als_it &= CM32181_CMD_ALS_IT_MASK;
	als_it >>= CM32181_CMD_ALS_IT_SHIFT;
	for (i = 0; i < ARRAY_SIZE(als_it_bits); i++) {
		if (als_it == als_it_bits[i]) {
			*val2 = als_it_value[i];
			return IIO_VAL_INT_PLUS_MICRO;
		}
	}

	return -EINVAL;
}