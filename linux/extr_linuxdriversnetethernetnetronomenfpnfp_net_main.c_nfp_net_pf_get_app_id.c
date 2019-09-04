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
struct nfp_pf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFP_APP_CORE_NIC ; 
 int nfp_pf_rtsym_read_optional (struct nfp_pf*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nfp_net_pf_get_app_id(struct nfp_pf *pf)
{
	return nfp_pf_rtsym_read_optional(pf, "_pf%u_net_app_id",
					  NFP_APP_CORE_NIC);
}