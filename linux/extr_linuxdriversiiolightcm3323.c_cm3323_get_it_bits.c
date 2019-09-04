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
struct cm3323_data {int reg_conf; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int CM3323_CONF_IT_MASK ; 
 int CM3323_CONF_IT_SHIFT ; 
 int EINVAL ; 
 int /*<<< orphan*/  cm3323_int_time ; 

__attribute__((used)) static int cm3323_get_it_bits(struct cm3323_data *data)
{
	int bits;

	bits = (data->reg_conf & CM3323_CONF_IT_MASK) >>
		CM3323_CONF_IT_SHIFT;

	if (bits >= ARRAY_SIZE(cm3323_int_time))
		return -EINVAL;

	return bits;
}