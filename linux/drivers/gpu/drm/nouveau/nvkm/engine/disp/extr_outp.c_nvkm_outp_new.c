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
struct nvkm_outp {int dummy; } ;
struct nvkm_disp {int dummy; } ;
struct dcb_output {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nvkm_outp* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_outp ; 
 int nvkm_outp_ctor (int /*<<< orphan*/ *,struct nvkm_disp*,int,struct dcb_output*,struct nvkm_outp*) ; 

int
nvkm_outp_new(struct nvkm_disp *disp, int index, struct dcb_output *dcbE,
	      struct nvkm_outp **poutp)
{
	if (!(*poutp = kzalloc(sizeof(**poutp), GFP_KERNEL)))
		return -ENOMEM;
	return nvkm_outp_ctor(&nvkm_outp, disp, index, dcbE, *poutp);
}