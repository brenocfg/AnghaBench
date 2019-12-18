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
typedef  int /*<<< orphan*/  uint16_t ;
struct lbs_private {int fwcapinfo; } ;
struct cmd_ds_mesh_config {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int FW_CAPINFO_PERSISTENT_CONFIG ; 
 int __lbs_mesh_config_send (struct lbs_private*,struct cmd_ds_mesh_config*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lbs_mesh_config_send(struct lbs_private *priv,
			 struct cmd_ds_mesh_config *cmd,
			 uint16_t action, uint16_t type)
{
	int ret;

	if (!(priv->fwcapinfo & FW_CAPINFO_PERSISTENT_CONFIG))
		return -EOPNOTSUPP;

	ret = __lbs_mesh_config_send(priv, cmd, action, type);
	return ret;
}