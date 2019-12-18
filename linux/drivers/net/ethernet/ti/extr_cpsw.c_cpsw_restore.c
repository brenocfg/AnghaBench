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
struct cpsw_priv {int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpsw_cbs_resume ; 
 int /*<<< orphan*/  cpsw_mqprio_resume ; 
 int /*<<< orphan*/  cpsw_restore_vlans ; 
 int /*<<< orphan*/  for_each_slave (struct cpsw_priv*,int /*<<< orphan*/ ,struct cpsw_priv*) ; 
 int /*<<< orphan*/  vlan_for_each (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cpsw_priv*) ; 

__attribute__((used)) static void cpsw_restore(struct cpsw_priv *priv)
{
	/* restore vlan configurations */
	vlan_for_each(priv->ndev, cpsw_restore_vlans, priv);

	/* restore MQPRIO offload */
	for_each_slave(priv, cpsw_mqprio_resume, priv);

	/* restore CBS offload */
	for_each_slave(priv, cpsw_cbs_resume, priv);
}