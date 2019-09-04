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
struct nvkm_i2c_pad {int dummy; } ;
struct nvkm_i2c {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gf119_i2c_pad_x_func ; 
 int nvkm_i2c_pad_new_ (int /*<<< orphan*/ *,struct nvkm_i2c*,int,struct nvkm_i2c_pad**) ; 

int
gf119_i2c_pad_x_new(struct nvkm_i2c *i2c, int id, struct nvkm_i2c_pad **ppad)
{
	return nvkm_i2c_pad_new_(&gf119_i2c_pad_x_func, i2c, id, ppad);
}