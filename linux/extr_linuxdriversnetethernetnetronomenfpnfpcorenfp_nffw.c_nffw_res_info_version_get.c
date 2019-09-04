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
struct nfp_nffw_info_data {int /*<<< orphan*/ * flags; } ;

/* Variables and functions */
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 nffw_res_info_version_get(const struct nfp_nffw_info_data *res)
{
	return (le32_to_cpu(res->flags[0]) >> 16) & 0xfff;
}