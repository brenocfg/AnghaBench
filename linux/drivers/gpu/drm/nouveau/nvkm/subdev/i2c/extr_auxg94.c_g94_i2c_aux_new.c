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
typedef  int /*<<< orphan*/  u8 ;
struct nvkm_i2c_pad {int dummy; } ;
struct nvkm_i2c_aux {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  g94_i2c_aux ; 
 int g94_i2c_aux_new_ (int /*<<< orphan*/ *,struct nvkm_i2c_pad*,int,int /*<<< orphan*/ ,struct nvkm_i2c_aux**) ; 

int
g94_i2c_aux_new(struct nvkm_i2c_pad *pad, int index, u8 drive,
		struct nvkm_i2c_aux **paux)
{
	return g94_i2c_aux_new_(&g94_i2c_aux, pad, index, drive, paux);
}