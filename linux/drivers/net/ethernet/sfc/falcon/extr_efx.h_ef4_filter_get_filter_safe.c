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
typedef  int /*<<< orphan*/  u32 ;
struct ef4_nic {TYPE_1__* type; } ;
struct ef4_filter_spec {int dummy; } ;
typedef  enum ef4_filter_priority { ____Placeholder_ef4_filter_priority } ef4_filter_priority ;
struct TYPE_2__ {int (* filter_get_safe ) (struct ef4_nic*,int,int /*<<< orphan*/ ,struct ef4_filter_spec*) ;} ;

/* Variables and functions */
 int stub1 (struct ef4_nic*,int,int /*<<< orphan*/ ,struct ef4_filter_spec*) ; 

__attribute__((used)) static inline int
ef4_filter_get_filter_safe(struct ef4_nic *efx,
			   enum ef4_filter_priority priority,
			   u32 filter_id, struct ef4_filter_spec *spec)
{
	return efx->type->filter_get_safe(efx, priority, filter_id, spec);
}