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
struct nvkm_i2c_pad {int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAD_TRACE (struct nvkm_i2c_pad*,char*) ; 
 int /*<<< orphan*/  kfree (struct nvkm_i2c_pad*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

void
nvkm_i2c_pad_del(struct nvkm_i2c_pad **ppad)
{
	struct nvkm_i2c_pad *pad = *ppad;
	if (pad) {
		PAD_TRACE(pad, "dtor");
		list_del(&pad->head);
		kfree(pad);
		pad = NULL;
	}
}