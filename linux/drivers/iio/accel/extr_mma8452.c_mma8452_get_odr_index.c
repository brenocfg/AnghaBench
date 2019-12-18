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
struct mma8452_data {unsigned int ctrl_reg1; } ;

/* Variables and functions */
 unsigned int MMA8452_CTRL_DR_MASK ; 
 unsigned int MMA8452_CTRL_DR_SHIFT ; 

__attribute__((used)) static unsigned int mma8452_get_odr_index(struct mma8452_data *data)
{
	return (data->ctrl_reg1 & MMA8452_CTRL_DR_MASK) >>
			MMA8452_CTRL_DR_SHIFT;
}