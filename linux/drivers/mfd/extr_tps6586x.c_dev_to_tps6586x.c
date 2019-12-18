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
struct tps6586x {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct tps6586x* i2c_get_clientdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_i2c_client (struct device*) ; 

__attribute__((used)) static inline struct tps6586x *dev_to_tps6586x(struct device *dev)
{
	return i2c_get_clientdata(to_i2c_client(dev));
}