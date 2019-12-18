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
 int /*<<< orphan*/  i2c_get_adapdata (struct i2c_adapter*) ; 
 int ocores_xfer_core (int /*<<< orphan*/ ,struct i2c_msg*,int,int) ; 

__attribute__((used)) static int ocores_xfer(struct i2c_adapter *adap,
		       struct i2c_msg *msgs, int num)
{
	return ocores_xfer_core(i2c_get_adapdata(adap), msgs, num, false);
}