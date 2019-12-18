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
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int i2c_encode_flags_to_addr (struct i2c_client*) ; 
 struct i2c_client* i2c_verify_client (struct device*) ; 

__attribute__((used)) static int __i2c_check_addr_busy(struct device *dev, void *addrp)
{
	struct i2c_client	*client = i2c_verify_client(dev);
	int			addr = *(int *)addrp;

	if (client && i2c_encode_flags_to_addr(client) == addr)
		return -EBUSY;
	return 0;
}