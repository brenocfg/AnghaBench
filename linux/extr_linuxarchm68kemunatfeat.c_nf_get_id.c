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
typedef  int /*<<< orphan*/  name_copy ;

/* Variables and functions */
 long nf_get_id_phys (int /*<<< orphan*/ ) ; 
 size_t strlcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  virt_to_phys (char*) ; 

long nf_get_id(const char *feature_name)
{
	/* feature_name may be in vmalloc()ed memory, so make a copy */
	char name_copy[32];
	size_t n;

	n = strlcpy(name_copy, feature_name, sizeof(name_copy));
	if (n >= sizeof(name_copy))
		return 0;

	return nf_get_id_phys(virt_to_phys(name_copy));
}