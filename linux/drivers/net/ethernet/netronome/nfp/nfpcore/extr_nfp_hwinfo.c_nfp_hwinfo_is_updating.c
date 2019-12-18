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
struct nfp_hwinfo {int /*<<< orphan*/  version; } ;

/* Variables and functions */
 int NFP_HWINFO_VERSION_UPDATING ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool nfp_hwinfo_is_updating(struct nfp_hwinfo *hwinfo)
{
	return le32_to_cpu(hwinfo->version) & NFP_HWINFO_VERSION_UPDATING;
}