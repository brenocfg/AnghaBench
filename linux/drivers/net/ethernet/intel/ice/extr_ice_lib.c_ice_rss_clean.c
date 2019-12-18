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
struct ice_vsi {int /*<<< orphan*/  rss_lut_user; int /*<<< orphan*/  rss_hkey_user; struct ice_pf* back; } ;
struct ice_pf {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ice_rss_clean(struct ice_vsi *vsi)
{
	struct ice_pf *pf;

	pf = vsi->back;

	if (vsi->rss_hkey_user)
		devm_kfree(&pf->pdev->dev, vsi->rss_hkey_user);
	if (vsi->rss_lut_user)
		devm_kfree(&pf->pdev->dev, vsi->rss_lut_user);
}