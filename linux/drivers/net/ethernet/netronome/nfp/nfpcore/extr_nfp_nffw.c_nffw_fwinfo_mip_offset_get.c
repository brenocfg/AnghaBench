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
typedef  int u64 ;
struct nffw_fwinfo {int /*<<< orphan*/  mip_offset_lo; int /*<<< orphan*/  loaded__mu_da__mip_off_hi; } ;

/* Variables and functions */
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 nffw_fwinfo_mip_offset_get(const struct nffw_fwinfo *fi)
{
	u64 mip_off_hi = le32_to_cpu(fi->loaded__mu_da__mip_off_hi);

	return (mip_off_hi & 0xFF) << 32 | le32_to_cpu(fi->mip_offset_lo);
}