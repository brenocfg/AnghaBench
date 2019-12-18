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
typedef  void* u32 ;
struct guc_ct_buffer_desc {void* owner; void* size; void* addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CT_DEBUG_DRIVER (char*,struct guc_ct_buffer_desc*,void*,void*,void*) ; 
 int /*<<< orphan*/  memset (struct guc_ct_buffer_desc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void guc_ct_buffer_desc_init(struct guc_ct_buffer_desc *desc,
				    u32 cmds_addr, u32 size, u32 owner)
{
	CT_DEBUG_DRIVER("CT: desc %p init addr=%#x size=%u owner=%u\n",
			desc, cmds_addr, size, owner);
	memset(desc, 0, sizeof(*desc));
	desc->addr = cmds_addr;
	desc->size = size;
	desc->owner = owner;
}