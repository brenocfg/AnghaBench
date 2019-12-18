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
struct nfp_pf {int /*<<< orphan*/  mip; } ;
struct nfp_dump_tl {int dummy; } ;

/* Variables and functions */
 int ALIGN8 (scalar_t__) ; 
 int /*<<< orphan*/  nfp_mip_name (int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nfp_calc_fwname_tlv_size(struct nfp_pf *pf)
{
	u32 fwname_len = strlen(nfp_mip_name(pf->mip));

	return sizeof(struct nfp_dump_tl) + ALIGN8(fwname_len + 1);
}