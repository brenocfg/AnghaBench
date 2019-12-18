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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_i2c_aux {TYPE_1__* func; } ;
struct TYPE_2__ {int (* xfer ) (struct nvkm_i2c_aux*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  address_only; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUX_ERR (struct nvkm_i2c_aux*,char*) ; 
 int ENOSYS ; 
 int stub1 (struct nvkm_i2c_aux*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
nvkm_i2c_aux_xfer(struct nvkm_i2c_aux *aux, bool retry, u8 type,
		  u32 addr, u8 *data, u8 *size)
{
	if (!*size && !aux->func->address_only) {
		AUX_ERR(aux, "address-only transaction dropped");
		return -ENOSYS;
	}
	return aux->func->xfer(aux, retry, type, addr, data, size);
}