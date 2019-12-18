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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {unsigned int major_id; unsigned int pack_id; unsigned int pack_mask; char const* name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* soc_packages ; 
 unsigned int socinfo_to_major (int /*<<< orphan*/ ) ; 
 unsigned int socinfo_to_pack (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *socinfo_to_package_id(u32 socinfo)
{
	unsigned int pack = socinfo_to_pack(socinfo);
	unsigned int major = socinfo_to_major(socinfo);
	int i;

	for (i = 0 ; i < ARRAY_SIZE(soc_packages) ; ++i) {
		if (soc_packages[i].major_id == major &&
		    soc_packages[i].pack_id ==
				(pack & soc_packages[i].pack_mask))
			return soc_packages[i].name;
	}

	return "Unknown";
}