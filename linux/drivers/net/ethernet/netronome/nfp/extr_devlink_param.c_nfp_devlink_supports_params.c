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
struct nfp_pf {TYPE_1__* pdev; int /*<<< orphan*/  cpp; } ;
struct nfp_nsp {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct nfp_nsp*) ; 
 int PTR_ERR (struct nfp_nsp*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  nfp_nsp_close (struct nfp_nsp*) ; 
 scalar_t__ nfp_nsp_has_hwinfo_lookup (struct nfp_nsp*) ; 
 scalar_t__ nfp_nsp_has_hwinfo_set (struct nfp_nsp*) ; 
 struct nfp_nsp* nfp_nsp_open (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nfp_devlink_supports_params(struct nfp_pf *pf)
{
	struct nfp_nsp *nsp;
	bool supported;
	int err;

	nsp = nfp_nsp_open(pf->cpp);
	if (IS_ERR(nsp)) {
		err = PTR_ERR(nsp);
		dev_err(&pf->pdev->dev, "Failed to access the NSP: %d\n", err);
		return err;
	}

	supported = nfp_nsp_has_hwinfo_lookup(nsp) &&
		    nfp_nsp_has_hwinfo_set(nsp);

	nfp_nsp_close(nsp);
	return supported;
}