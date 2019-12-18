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
typedef  enum nfp_bpf_map_use { ____Placeholder_nfp_bpf_map_use } nfp_bpf_map_use ;

/* Variables and functions */
 int ARRAY_SIZE (char const* const*) ; 
#define  NFP_MAP_UNUSED 131 
#define  NFP_MAP_USE_ATOMIC_CNT 130 
#define  NFP_MAP_USE_READ 129 
#define  NFP_MAP_USE_WRITE 128 

__attribute__((used)) static const char *nfp_bpf_map_use_name(enum nfp_bpf_map_use use)
{
	static const char * const names[] = {
		[NFP_MAP_UNUSED]	= "unused",
		[NFP_MAP_USE_READ]	= "read",
		[NFP_MAP_USE_WRITE]	= "write",
		[NFP_MAP_USE_ATOMIC_CNT] = "atomic",
	};

	if (use >= ARRAY_SIZE(names) || !names[use])
		return "unknown";
	return names[use];
}