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
struct nfp_flower_priv {int /*<<< orphan*/  nn; } ;
struct nfp_app {struct nfp_flower_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFP_FLOWER_CMSG_PORT_VNIC_TYPE_VF ; 
 int /*<<< orphan*/  NFP_REPR_TYPE_VF ; 
 int nfp_flower_spawn_vnic_reprs (struct nfp_app*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int nfp_flower_sriov_enable(struct nfp_app *app, int num_vfs)
{
	struct nfp_flower_priv *priv = app->priv;

	if (!priv->nn)
		return 0;

	return nfp_flower_spawn_vnic_reprs(app,
					   NFP_FLOWER_CMSG_PORT_VNIC_TYPE_VF,
					   NFP_REPR_TYPE_VF, num_vfs);
}