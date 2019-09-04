#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* cra_name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* drbg_cores ; 
 int /*<<< orphan*/  memcmp (char const*,char*,int) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static inline void drbg_convert_tfm_core(const char *cra_driver_name,
					 int *coreref, bool *pr)
{
	int i = 0;
	size_t start = 0;
	int len = 0;

	*pr = true;
	/* disassemble the names */
	if (!memcmp(cra_driver_name, "drbg_nopr_", 10)) {
		start = 10;
		*pr = false;
	} else if (!memcmp(cra_driver_name, "drbg_pr_", 8)) {
		start = 8;
	} else {
		return;
	}

	/* remove the first part */
	len = strlen(cra_driver_name) - start;
	for (i = 0; ARRAY_SIZE(drbg_cores) > i; i++) {
		if (!memcmp(cra_driver_name + start, drbg_cores[i].cra_name,
			    len)) {
			*coreref = i;
			return;
		}
	}
}