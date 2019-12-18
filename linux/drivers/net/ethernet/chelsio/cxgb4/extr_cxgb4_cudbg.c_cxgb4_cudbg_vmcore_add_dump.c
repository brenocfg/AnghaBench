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
struct vmcoredd_data {int size; int /*<<< orphan*/  vmcoredd_callback; int /*<<< orphan*/  dump_name; } ;
struct cudbg_hdr {int dummy; } ;
struct cudbg_entity_hdr {int dummy; } ;
struct adapter {char* name; struct vmcoredd_data vmcoredd; } ;

/* Variables and functions */
 scalar_t__ CUDBG_DUMP_BUFF_SIZE ; 
 int CUDBG_MAX_ENTITY ; 
 int /*<<< orphan*/  cxgb4_cudbg_vmcoredd_collect ; 
 char* cxgb4_driver_name ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,char*) ; 
 int vmcore_add_device_dump (struct vmcoredd_data*) ; 

int cxgb4_cudbg_vmcore_add_dump(struct adapter *adap)
{
	struct vmcoredd_data *data = &adap->vmcoredd;
	u32 len;

	len = sizeof(struct cudbg_hdr) +
	      sizeof(struct cudbg_entity_hdr) * CUDBG_MAX_ENTITY;
	len += CUDBG_DUMP_BUFF_SIZE;

	data->size = len;
	snprintf(data->dump_name, sizeof(data->dump_name), "%s_%s",
		 cxgb4_driver_name, adap->name);
	data->vmcoredd_callback = cxgb4_cudbg_vmcoredd_collect;

	return vmcore_add_device_dump(data);
}