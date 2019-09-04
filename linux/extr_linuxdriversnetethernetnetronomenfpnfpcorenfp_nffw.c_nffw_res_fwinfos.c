#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct nffw_fwinfo* fwinfo; } ;
struct TYPE_4__ {struct nffw_fwinfo* fwinfo; } ;
struct TYPE_6__ {TYPE_2__ v2; TYPE_1__ v1; } ;
struct nfp_nffw_info_data {TYPE_3__ info; } ;
struct nffw_fwinfo {int dummy; } ;

/* Variables and functions */
 unsigned int NFFW_FWINFO_CNT_V1 ; 
 unsigned int NFFW_FWINFO_CNT_V2 ; 
 int nffw_res_info_version_get (struct nfp_nffw_info_data*) ; 

__attribute__((used)) static unsigned int
nffw_res_fwinfos(struct nfp_nffw_info_data *fwinf, struct nffw_fwinfo **arr)
{
	/* For the this code, version 0 is most likely to be
	 * version 1 in this case. Since the kernel driver
	 * does not take responsibility for initialising the
	 * nfp.nffw resource, any previous code (CA firmware or
	 * userspace) that left the version 0 and did set
	 * the init flag is going to be version 1.
	 */
	switch (nffw_res_info_version_get(fwinf)) {
	case 0:
	case 1:
		*arr = &fwinf->info.v1.fwinfo[0];
		return NFFW_FWINFO_CNT_V1;
	case 2:
		*arr = &fwinf->info.v2.fwinfo[0];
		return NFFW_FWINFO_CNT_V2;
	default:
		*arr = NULL;
		return 0;
	}
}