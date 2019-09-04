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
struct nvkm_disp_oclass {int dummy; } ;
struct nvkm_disp {int dummy; } ;

/* Variables and functions */
 struct nvkm_disp_oclass const nv04_disp_root_oclass ; 

__attribute__((used)) static const struct nvkm_disp_oclass *
nv04_disp_root(struct nvkm_disp *disp)
{
	return &nv04_disp_root_oclass;
}