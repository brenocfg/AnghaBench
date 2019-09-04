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
typedef  int u8 ;
struct mms114_data {int cache_mode_control; } ;

/* Variables and functions */
 unsigned int MMS114_MODE_CONTROL ; 
 int __mms114_read_reg (struct mms114_data*,unsigned int,int,int*) ; 

__attribute__((used)) static int mms114_read_reg(struct mms114_data *data, unsigned int reg)
{
	u8 val;
	int error;

	if (reg == MMS114_MODE_CONTROL)
		return data->cache_mode_control;

	error = __mms114_read_reg(data, reg, 1, &val);
	return error < 0 ? error : val;
}