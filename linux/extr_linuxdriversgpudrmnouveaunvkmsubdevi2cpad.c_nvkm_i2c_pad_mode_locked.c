#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nvkm_i2c_pad {TYPE_1__* func; } ;
typedef  enum nvkm_i2c_pad_mode { ____Placeholder_nvkm_i2c_pad_mode } nvkm_i2c_pad_mode ;
struct TYPE_2__ {int /*<<< orphan*/  (* mode ) (struct nvkm_i2c_pad*,int) ;} ;

/* Variables and functions */
 int NVKM_I2C_PAD_AUX ; 
 int NVKM_I2C_PAD_I2C ; 
 int /*<<< orphan*/  PAD_TRACE (struct nvkm_i2c_pad*,char*,char*) ; 
 int /*<<< orphan*/  stub1 (struct nvkm_i2c_pad*,int) ; 

__attribute__((used)) static void
nvkm_i2c_pad_mode_locked(struct nvkm_i2c_pad *pad, enum nvkm_i2c_pad_mode mode)
{
	PAD_TRACE(pad, "-> %s", (mode == NVKM_I2C_PAD_AUX) ? "aux" :
			      (mode == NVKM_I2C_PAD_I2C) ? "i2c" : "off");
	if (pad->func->mode)
		pad->func->mode(pad, mode);
}