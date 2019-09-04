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
struct nvkm_i2c_pad {int id; int /*<<< orphan*/  head; int /*<<< orphan*/  mutex; int /*<<< orphan*/  mode; struct nvkm_i2c* i2c; struct nvkm_i2c_pad_func const* func; } ;
struct nvkm_i2c {int /*<<< orphan*/  pad; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVKM_I2C_PAD_OFF ; 
 int /*<<< orphan*/  PAD_TRACE (struct nvkm_i2c_pad*,char*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

void
nvkm_i2c_pad_ctor(const struct nvkm_i2c_pad_func *func, struct nvkm_i2c *i2c,
		  int id, struct nvkm_i2c_pad *pad)
{
	pad->func = func;
	pad->i2c = i2c;
	pad->id = id;
	pad->mode = NVKM_I2C_PAD_OFF;
	mutex_init(&pad->mutex);
	list_add_tail(&pad->head, &i2c->pad);
	PAD_TRACE(pad, "ctor");
}