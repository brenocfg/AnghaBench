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
struct ltc2978_data {int dummy; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 scalar_t__ lin11_to_val (int) ; 
 int ltc_read_word_data (struct i2c_client*,int,int) ; 

__attribute__((used)) static int ltc_get_max(struct ltc2978_data *data, struct i2c_client *client,
		       int page, int reg, u16 *pmax)
{
	int ret;

	ret = ltc_read_word_data(client, page, reg);
	if (ret >= 0) {
		if (lin11_to_val(ret) > lin11_to_val(*pmax))
			*pmax = ret;
		ret = *pmax;
	}
	return ret;
}