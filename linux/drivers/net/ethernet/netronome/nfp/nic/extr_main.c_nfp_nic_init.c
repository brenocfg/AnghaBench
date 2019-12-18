#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nfp_pf {scalar_t__ max_data_vnics; TYPE_1__* eth_tbl; int /*<<< orphan*/  cpp; } ;
struct nfp_app {struct nfp_pf* pf; } ;
struct TYPE_2__ {scalar_t__ count; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  nfp_err (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int nfp_nic_init(struct nfp_app *app)
{
	struct nfp_pf *pf = app->pf;

	if (pf->eth_tbl && pf->max_data_vnics != pf->eth_tbl->count) {
		nfp_err(pf->cpp, "ETH entries don't match vNICs (%d vs %d)\n",
			pf->max_data_vnics, pf->eth_tbl->count);
		return -EINVAL;
	}

	return 0;
}