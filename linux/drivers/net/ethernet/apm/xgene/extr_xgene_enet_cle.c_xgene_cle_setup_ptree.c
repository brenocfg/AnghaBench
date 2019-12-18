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
struct xgene_enet_pdata {int dummy; } ;
struct xgene_enet_cle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  xgene_cle_enable_ptree (struct xgene_enet_pdata*,struct xgene_enet_cle*) ; 
 int xgene_cle_setup_dbptr (struct xgene_enet_pdata*,struct xgene_enet_cle*) ; 
 int xgene_cle_setup_node (struct xgene_enet_pdata*,struct xgene_enet_cle*) ; 

__attribute__((used)) static int xgene_cle_setup_ptree(struct xgene_enet_pdata *pdata,
				 struct xgene_enet_cle *cle)
{
	int ret;

	ret = xgene_cle_setup_node(pdata, cle);
	if (ret)
		return ret;

	ret = xgene_cle_setup_dbptr(pdata, cle);
	if (ret)
		return ret;

	xgene_cle_enable_ptree(pdata, cle);

	return 0;
}