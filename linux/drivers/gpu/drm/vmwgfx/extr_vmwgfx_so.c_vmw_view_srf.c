#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vmw_resource {int dummy; } ;
struct TYPE_2__ {struct vmw_resource* srf; } ;

/* Variables and functions */
 TYPE_1__* vmw_view (struct vmw_resource*) ; 

struct vmw_resource *vmw_view_srf(struct vmw_resource *res)
{
	return vmw_view(res)->srf;
}