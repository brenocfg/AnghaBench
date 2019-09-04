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
struct nvkm_i2c_aux {int /*<<< orphan*/  i2c; int /*<<< orphan*/  head; int /*<<< orphan*/  func; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUX_TRACE (struct nvkm_i2c_aux*,char*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct nvkm_i2c_aux*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

void
nvkm_i2c_aux_del(struct nvkm_i2c_aux **paux)
{
	struct nvkm_i2c_aux *aux = *paux;
	if (aux && !WARN_ON(!aux->func)) {
		AUX_TRACE(aux, "dtor");
		list_del(&aux->head);
		i2c_del_adapter(&aux->i2c);
		kfree(*paux);
		*paux = NULL;
	}
}