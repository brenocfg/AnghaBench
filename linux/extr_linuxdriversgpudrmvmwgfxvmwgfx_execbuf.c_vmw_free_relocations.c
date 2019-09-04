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
struct vmw_sw_context {scalar_t__ cur_reloc; } ;

/* Variables and functions */

__attribute__((used)) static void vmw_free_relocations(struct vmw_sw_context *sw_context)
{
	sw_context->cur_reloc = 0;
}