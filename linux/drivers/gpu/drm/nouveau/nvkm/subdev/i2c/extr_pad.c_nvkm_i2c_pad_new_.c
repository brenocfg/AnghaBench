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
struct nvkm_i2c_pad_func {int dummy; } ;
struct nvkm_i2c_pad {int dummy; } ;
struct nvkm_i2c {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nvkm_i2c_pad* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_i2c_pad_ctor (struct nvkm_i2c_pad_func const*,struct nvkm_i2c*,int,struct nvkm_i2c_pad*) ; 

int
nvkm_i2c_pad_new_(const struct nvkm_i2c_pad_func *func, struct nvkm_i2c *i2c,
		  int id, struct nvkm_i2c_pad **ppad)
{
	if (!(*ppad = kzalloc(sizeof(**ppad), GFP_KERNEL)))
		return -ENOMEM;
	nvkm_i2c_pad_ctor(func, i2c, id, *ppad);
	return 0;
}