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
struct nvkm_falcon {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct nvkm_falcon*) ; 

void
nvkm_falcon_del(struct nvkm_falcon **pfalcon)
{
	if (*pfalcon) {
		kfree(*pfalcon);
		*pfalcon = NULL;
	}
}