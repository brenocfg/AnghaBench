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
struct nvkm_secboot {TYPE_1__* acr; } ;
typedef  enum nvkm_secboot_falcon { ____Placeholder_nvkm_secboot_falcon } nvkm_secboot_falcon ;
struct TYPE_2__ {int managed_falcons; } ;

/* Variables and functions */
 int BIT (int) ; 

bool
nvkm_secboot_is_managed(struct nvkm_secboot *sb, enum nvkm_secboot_falcon fid)
{
	if (!sb)
		return false;

	return sb->acr->managed_falcons & BIT(fid);
}