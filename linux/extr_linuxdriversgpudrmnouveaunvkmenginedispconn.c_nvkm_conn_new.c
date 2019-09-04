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
struct nvkm_disp {int dummy; } ;
struct nvkm_conn {int dummy; } ;
struct nvbios_connE {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nvkm_conn* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_conn_ctor (struct nvkm_disp*,int,struct nvbios_connE*,struct nvkm_conn*) ; 

int
nvkm_conn_new(struct nvkm_disp *disp, int index, struct nvbios_connE *info,
	      struct nvkm_conn **pconn)
{
	if (!(*pconn = kzalloc(sizeof(**pconn), GFP_KERNEL)))
		return -ENOMEM;
	nvkm_conn_ctor(disp, index, info, *pconn);
	return 0;
}