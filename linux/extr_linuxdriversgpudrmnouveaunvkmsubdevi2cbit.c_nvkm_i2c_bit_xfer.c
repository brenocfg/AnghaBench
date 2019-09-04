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
struct nvkm_i2c_bus {int dummy; } ;
struct i2c_msg {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 

int
nvkm_i2c_bit_xfer(struct nvkm_i2c_bus *bus, struct i2c_msg *msgs, int num)
{
	return -ENODEV;
}