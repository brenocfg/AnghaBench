#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct etnaviv_chip_identity {scalar_t__ model; scalar_t__ revision; } ;
struct etnaviv_gpu {struct etnaviv_chip_identity identity; } ;
struct TYPE_4__ {scalar_t__ model; scalar_t__ revision; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* etnaviv_chip_identities ; 
 int /*<<< orphan*/  memcpy (struct etnaviv_chip_identity*,TYPE_1__*,int) ; 

bool etnaviv_fill_identity_from_hwdb(struct etnaviv_gpu *gpu)
{
	struct etnaviv_chip_identity *ident = &gpu->identity;
	int i;

	for (i = 0; i < ARRAY_SIZE(etnaviv_chip_identities); i++) {
		if (etnaviv_chip_identities[i].model == ident->model &&
		    etnaviv_chip_identities[i].revision == ident->revision) {
			memcpy(ident, &etnaviv_chip_identities[i],
			       sizeof(*ident));
			return true;
		}
	}

	return false;
}