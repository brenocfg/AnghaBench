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
typedef  int u32 ;
struct nvkm_nvsw {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  NV04_NVSW_GET_REF 128 
 int nv04_nvsw_mthd_get_ref (struct nvkm_nvsw*,void*,int) ; 

__attribute__((used)) static int
nv04_nvsw_mthd(struct nvkm_nvsw *nvsw, u32 mthd, void *data, u32 size)
{
	switch (mthd) {
	case NV04_NVSW_GET_REF:
		return nv04_nvsw_mthd_get_ref(nvsw, data, size);
	default:
		break;
	}
	return -EINVAL;
}