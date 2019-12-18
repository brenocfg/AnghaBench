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
struct nvkm_i2c_pad {int mode; int /*<<< orphan*/  mutex; } ;
typedef  enum nvkm_i2c_pad_mode { ____Placeholder_nvkm_i2c_pad_mode } nvkm_i2c_pad_mode ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ NVKM_I2C_PAD_OFF ; 
 int /*<<< orphan*/  PAD_TRACE (struct nvkm_i2c_pad*,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_i2c_pad_mode_locked (struct nvkm_i2c_pad*,int) ; 

int
nvkm_i2c_pad_acquire(struct nvkm_i2c_pad *pad, enum nvkm_i2c_pad_mode mode)
{
	PAD_TRACE(pad, "acquire");
	mutex_lock(&pad->mutex);
	if (pad->mode != mode) {
		if (pad->mode != NVKM_I2C_PAD_OFF) {
			mutex_unlock(&pad->mutex);
			return -EBUSY;
		}
		nvkm_i2c_pad_mode_locked(pad, mode);
	}
	return 0;
}