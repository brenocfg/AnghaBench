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
struct nvkm_ramht {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_ramht_update (struct nvkm_ramht*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
nvkm_ramht_remove(struct nvkm_ramht *ramht, int cookie)
{
	if (--cookie >= 0)
		nvkm_ramht_update(ramht, cookie, NULL, -1, 0, 0, 0);
}