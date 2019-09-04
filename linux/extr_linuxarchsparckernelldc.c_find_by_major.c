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
typedef  scalar_t__ u16 ;
struct ldc_version {scalar_t__ major; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct ldc_version*) ; 
 struct ldc_version* ver_arr ; 

__attribute__((used)) static struct ldc_version *find_by_major(u16 major)
{
	struct ldc_version *ret = NULL;
	int i;

	for (i = 0; i < ARRAY_SIZE(ver_arr); i++) {
		struct ldc_version *v = &ver_arr[i];
		if (v->major <= major) {
			ret = v;
			break;
		}
	}
	return ret;
}