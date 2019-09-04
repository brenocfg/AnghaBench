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
struct handler_common_data {void (* handler ) (void*) ;struct amdgpu_display_manager* dm; void* handler_arg; } ;
struct amdgpu_display_manager {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void init_handler_common_data(struct handler_common_data *hcd,
				     void (*ih)(void *),
				     void *args,
				     struct amdgpu_display_manager *dm)
{
	hcd->handler = ih;
	hcd->handler_arg = args;
	hcd->dm = dm;
}