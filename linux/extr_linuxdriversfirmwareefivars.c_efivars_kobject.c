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
struct kobject {int dummy; } ;
struct TYPE_2__ {struct kobject* kobject; } ;

/* Variables and functions */
 TYPE_1__* __efivars ; 

struct kobject *efivars_kobject(void)
{
	if (!__efivars)
		return NULL;

	return __efivars->kobject;
}