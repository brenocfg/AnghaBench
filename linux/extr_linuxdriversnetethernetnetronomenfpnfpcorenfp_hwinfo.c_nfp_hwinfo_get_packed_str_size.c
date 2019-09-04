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
typedef  scalar_t__ u32 ;
struct nfp_hwinfo {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 

u32 nfp_hwinfo_get_packed_str_size(struct nfp_hwinfo *hwinfo)
{
	return le32_to_cpu(hwinfo->size) - sizeof(u32);
}