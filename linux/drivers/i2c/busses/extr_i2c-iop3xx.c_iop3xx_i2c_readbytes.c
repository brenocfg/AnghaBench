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
struct i2c_algo_iop3xx_data {int dummy; } ;
struct i2c_adapter {struct i2c_algo_iop3xx_data* algo_data; } ;

/* Variables and functions */
 int iop3xx_i2c_read_byte (struct i2c_algo_iop3xx_data*,char*,int) ; 

__attribute__((used)) static int
iop3xx_i2c_readbytes(struct i2c_adapter *i2c_adap, char *buf, int count)
{
	struct i2c_algo_iop3xx_data *iop3xx_adap = i2c_adap->algo_data;
	int ii;
	int rc = 0;

	for (ii = 0; rc == 0 && ii != count; ++ii)
		rc = iop3xx_i2c_read_byte(iop3xx_adap, &buf[ii], ii==count-1);

	return rc;
}