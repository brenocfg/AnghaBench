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
struct nvkm_i2c_pad {scalar_t__ mode; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 scalar_t__ NVKM_I2C_PAD_OFF ; 
 int /*<<< orphan*/  PAD_TRACE (struct nvkm_i2c_pad*,char*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_i2c_pad_mode_locked (struct nvkm_i2c_pad*,scalar_t__) ; 

void
nvkm_i2c_pad_release(struct nvkm_i2c_pad *pad)
{
	PAD_TRACE(pad, "release");
	if (pad->mode == NVKM_I2C_PAD_OFF)
		nvkm_i2c_pad_mode_locked(pad, pad->mode);
	mutex_unlock(&pad->mutex);
}