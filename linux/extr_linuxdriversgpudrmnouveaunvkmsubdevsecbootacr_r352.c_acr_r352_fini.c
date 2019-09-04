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
struct nvkm_secboot {int dummy; } ;
struct nvkm_acr {int dummy; } ;
struct acr_r352 {int dummy; } ;

/* Variables and functions */
 struct acr_r352* acr_r352 (struct nvkm_acr*) ; 
 int acr_r352_shutdown (struct acr_r352*,struct nvkm_secboot*) ; 

__attribute__((used)) static int
acr_r352_fini(struct nvkm_acr *_acr, struct nvkm_secboot *sb, bool suspend)
{
	struct acr_r352 *acr = acr_r352(_acr);

	return acr_r352_shutdown(acr, sb);
}