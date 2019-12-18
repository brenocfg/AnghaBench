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
typedef  int /*<<< orphan*/  grant_ref_t ;
struct TYPE_2__ {int (* end_foreign_access_ref ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 TYPE_1__* gnttab_interface ; 
 int stub1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int _gnttab_end_foreign_access_ref(grant_ref_t ref, int readonly)
{
	return gnttab_interface->end_foreign_access_ref(ref, readonly);
}