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
struct nvkm_nvdec {int dummy; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int nvkm_nvdec_new_ (struct nvkm_device*,int,struct nvkm_nvdec**) ; 

int
gp102_nvdec_new(struct nvkm_device *device, int index,
		struct nvkm_nvdec **pnvdec)
{
	return nvkm_nvdec_new_(device, index, pnvdec);
}