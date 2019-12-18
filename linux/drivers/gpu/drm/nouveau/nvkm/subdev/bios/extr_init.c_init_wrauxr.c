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
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_i2c_aux {int dummy; } ;
struct nvbios_init {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 struct nvkm_i2c_aux* init_aux (struct nvbios_init*) ; 
 scalar_t__ init_exec (struct nvbios_init*) ; 
 int nvkm_wraux (struct nvkm_i2c_aux*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  trace (char*,int) ; 

__attribute__((used)) static int
init_wrauxr(struct nvbios_init *init, u32 addr, u8 data)
{
	struct nvkm_i2c_aux *aux = init_aux(init);
	if (aux && init_exec(init)) {
		int ret = nvkm_wraux(aux, addr, &data, 1);
		if (ret)
			trace("auxch write failed with %d\n", ret);
		return ret;
	}
	return -ENODEV;
}