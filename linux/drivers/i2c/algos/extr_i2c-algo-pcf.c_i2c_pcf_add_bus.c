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
struct i2c_algo_pcf_data {int dummy; } ;
struct i2c_adapter {int /*<<< orphan*/ * algo; int /*<<< orphan*/  dev; struct i2c_algo_pcf_data* algo_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEB2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int i2c_add_adapter (struct i2c_adapter*) ; 
 int /*<<< orphan*/  pcf_algo ; 
 int pcf_init_8584 (struct i2c_algo_pcf_data*) ; 

int i2c_pcf_add_bus(struct i2c_adapter *adap)
{
	struct i2c_algo_pcf_data *pcf_adap = adap->algo_data;
	int rval;

	DEB2(dev_dbg(&adap->dev, "hw routines registered.\n"));

	/* register new adapter to i2c module... */
	adap->algo = &pcf_algo;

	if ((rval = pcf_init_8584(pcf_adap)))
		return rval;

	rval = i2c_add_adapter(adap);

	return rval;
}