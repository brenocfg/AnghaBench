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
struct nvkm_i2c_pad {int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAD_TRACE (struct nvkm_i2c_pad*,char*) ; 
 int /*<<< orphan*/  nvkm_i2c_pad_mode_locked (struct nvkm_i2c_pad*,int /*<<< orphan*/ ) ; 

void
nvkm_i2c_pad_init(struct nvkm_i2c_pad *pad)
{
	PAD_TRACE(pad, "init");
	nvkm_i2c_pad_mode_locked(pad, pad->mode);
}