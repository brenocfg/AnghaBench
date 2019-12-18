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
 int omap_i2c_xfer_common (struct i2c_adapter*,struct i2c_msg*,int,int) ; 

__attribute__((used)) static int
omap_i2c_xfer_polling(struct i2c_adapter *adap, struct i2c_msg msgs[], int num)
{
	return omap_i2c_xfer_common(adap, msgs, num, true);
}