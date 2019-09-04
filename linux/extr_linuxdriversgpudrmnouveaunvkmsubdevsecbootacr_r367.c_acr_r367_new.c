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
struct nvkm_acr {int dummy; } ;
typedef  enum nvkm_secboot_falcon { ____Placeholder_nvkm_secboot_falcon } nvkm_secboot_falcon ;

/* Variables and functions */
 struct nvkm_acr* acr_r352_new_ (int /*<<< orphan*/ *,int,unsigned long) ; 
 int /*<<< orphan*/  acr_r367_func ; 

struct nvkm_acr *
acr_r367_new(enum nvkm_secboot_falcon boot_falcon,
	     unsigned long managed_falcons)
{
	return acr_r352_new_(&acr_r367_func, boot_falcon, managed_falcons);
}