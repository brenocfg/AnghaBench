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
struct nfp_flower_priv {int /*<<< orphan*/  flower_version; } ;
struct TYPE_2__ {int /*<<< orphan*/  flow_version; int /*<<< orphan*/  flags; } ;
struct nfp_fl_payload {TYPE_1__ meta; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFP_FL_META_FLAG_MANAGE_MASK ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 

void __nfp_modify_flow_metadata(struct nfp_flower_priv *priv,
				struct nfp_fl_payload *nfp_flow)
{
	nfp_flow->meta.flags &= ~NFP_FL_META_FLAG_MANAGE_MASK;
	nfp_flow->meta.flow_version = cpu_to_be64(priv->flower_version);
	priv->flower_version++;
}