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
typedef  int u32 ;
struct nfp_hwinfo {char* data; } ;
struct nfp_cpp {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  nfp_warn (struct nfp_cpp*,char*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int
hwinfo_db_walk(struct nfp_cpp *cpp, struct nfp_hwinfo *hwinfo, u32 size)
{
	const char *key, *val, *end = hwinfo->data + size;

	for (key = hwinfo->data; *key && key < end;
	     key = val + strlen(val) + 1) {

		val = key + strlen(key) + 1;
		if (val >= end) {
			nfp_warn(cpp, "Bad HWINFO - overflowing key\n");
			return -EINVAL;
		}

		if (val + strlen(val) + 1 > end) {
			nfp_warn(cpp, "Bad HWINFO - overflowing value\n");
			return -EINVAL;
		}
	}

	return 0;
}