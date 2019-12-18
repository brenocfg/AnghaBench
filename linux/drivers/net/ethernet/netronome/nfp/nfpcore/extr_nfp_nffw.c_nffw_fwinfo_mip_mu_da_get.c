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
struct nffw_fwinfo {int /*<<< orphan*/  loaded__mu_da__mip_off_hi; } ;

/* Variables and functions */
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 nffw_fwinfo_mip_mu_da_get(const struct nffw_fwinfo *fi)
{
	return (le32_to_cpu(fi->loaded__mu_da__mip_off_hi) >> 8) & 1;
}