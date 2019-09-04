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
struct i2c_pnx_algo_data {long timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_REG_CTL (struct i2c_pnx_algo_data*) ; 
 int ioread32 (int /*<<< orphan*/ ) ; 
 int mcntrl_reset ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static inline int wait_reset(struct i2c_pnx_algo_data *data)
{
	long timeout = data->timeout;
	while (timeout > 0 &&
			(ioread32(I2C_REG_CTL(data)) & mcntrl_reset)) {
		mdelay(1);
		timeout--;
	}
	return (timeout <= 0);
}