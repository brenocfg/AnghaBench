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
struct nvkm_i2c_aux {int /*<<< orphan*/  mutex; struct nvkm_i2c_pad* pad; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUX_TRACE (struct nvkm_i2c_aux*,char*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_i2c_pad_release (struct nvkm_i2c_pad*) ; 

void
nvkm_i2c_aux_release(struct nvkm_i2c_aux *aux)
{
	struct nvkm_i2c_pad *pad = aux->pad;
	AUX_TRACE(aux, "release");
	nvkm_i2c_pad_release(pad);
	mutex_unlock(&aux->mutex);
}