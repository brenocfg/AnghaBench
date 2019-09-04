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
struct i2c_msg {int dummy; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int dib8096p_tuner_read_serpar (struct i2c_adapter*,struct i2c_msg*,int) ; 
 int dib8096p_tuner_write_serpar (struct i2c_adapter*,struct i2c_msg*,int) ; 
 scalar_t__ map_addr_to_serpar_number (struct i2c_msg*) ; 

__attribute__((used)) static int dib8096p_tuner_rw_serpar(struct i2c_adapter *i2c_adap,
		struct i2c_msg msg[], int num)
{
	if (map_addr_to_serpar_number(&msg[0]) == 0) {
		if (num == 1) /* write */
			return dib8096p_tuner_write_serpar(i2c_adap, msg, 1);
		else /* read */
			return dib8096p_tuner_read_serpar(i2c_adap, msg, 2);
	}
	return num;
}