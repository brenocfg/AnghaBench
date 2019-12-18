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
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int nv04_gr_mthd_bind_class (struct nvkm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv04_gr_set_ctx1 (struct nvkm_device*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static bool
nv01_gr_mthd_bind_chroma(struct nvkm_device *device, u32 inst, u32 data)
{
	switch (nv04_gr_mthd_bind_class(device, data)) {
	case 0x30:
		nv04_gr_set_ctx1(device, inst, 0x1000, 0);
		return true;
	/* Yes, for some reason even the old versions of objects
	 * accept 0x57 and not 0x17. Consistency be damned.
	 */
	case 0x57:
		nv04_gr_set_ctx1(device, inst, 0x1000, 0x1000);
		return true;
	}
	return false;
}