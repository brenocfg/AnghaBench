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
struct nvkm_i2c_aux_func {int dummy; } ;
struct nvkm_i2c_aux {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nvkm_i2c_aux* kzalloc (int,int /*<<< orphan*/ ) ; 
 int nvkm_i2c_aux_ctor (struct nvkm_i2c_aux_func const*,struct nvkm_i2c_pad*,int,struct nvkm_i2c_aux*) ; 

int
nvkm_i2c_aux_new_(const struct nvkm_i2c_aux_func *func,
		  struct nvkm_i2c_pad *pad, int id,
		  struct nvkm_i2c_aux **paux)
{
	if (!(*paux = kzalloc(sizeof(**paux), GFP_KERNEL)))
		return -ENOMEM;
	return nvkm_i2c_aux_ctor(func, pad, id, *paux);
}