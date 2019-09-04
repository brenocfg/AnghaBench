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
struct gfar_private {int dummy; } ;
struct ethtool_rxnfc {int /*<<< orphan*/  flow_type; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  gfar_ethflow_to_filer_table (struct gfar_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gfar_set_hash_opts(struct gfar_private *priv,
			      struct ethtool_rxnfc *cmd)
{
	/* write the filer rules here */
	if (!gfar_ethflow_to_filer_table(priv, cmd->data, cmd->flow_type))
		return -EINVAL;

	return 0;
}