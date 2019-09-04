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
struct nvdimm {int dummy; } ;

/* Variables and functions */
 int xlat_bus_status (void*,unsigned int,int /*<<< orphan*/ ) ; 
 int xlat_nvdimm_status (struct nvdimm*,void*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xlat_status(struct nvdimm *nvdimm, void *buf, unsigned int cmd,
		u32 status)
{
	if (!nvdimm)
		return xlat_bus_status(buf, cmd, status);
	return xlat_nvdimm_status(nvdimm, buf, cmd, status);
}