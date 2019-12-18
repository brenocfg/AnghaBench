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
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EXC3000_LEN_FRAME ; 
 int EXC3000_NUM_SLOTS ; 
 int EXC3000_SLOTS_PER_FRAME ; 
 int exc3000_read_frame (struct i2c_client*,int*) ; 

__attribute__((used)) static int exc3000_read_data(struct i2c_client *client,
			     u8 *buf, int *n_slots)
{
	int error;

	error = exc3000_read_frame(client, buf);
	if (error)
		return error;

	*n_slots = buf[3];
	if (!*n_slots || *n_slots > EXC3000_NUM_SLOTS)
		return -EINVAL;

	if (*n_slots > EXC3000_SLOTS_PER_FRAME) {
		/* Read 2nd frame to get the rest of the contacts. */
		error = exc3000_read_frame(client, buf + EXC3000_LEN_FRAME);
		if (error)
			return error;

		/* 2nd chunk must have number of contacts set to 0. */
		if (buf[EXC3000_LEN_FRAME + 3] != 0)
			return -EINVAL;
	}

	return 0;
}