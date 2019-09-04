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
struct ahci_host_priv {int nports; scalar_t__* target_pwrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  regulator_disable (scalar_t__) ; 
 int regulator_enable (scalar_t__) ; 

int ahci_platform_enable_regulators(struct ahci_host_priv *hpriv)
{
	int rc, i;

	for (i = 0; i < hpriv->nports; i++) {
		if (!hpriv->target_pwrs[i])
			continue;

		rc = regulator_enable(hpriv->target_pwrs[i]);
		if (rc)
			goto disable_target_pwrs;
	}

	return 0;

disable_target_pwrs:
	while (--i >= 0)
		if (hpriv->target_pwrs[i])
			regulator_disable(hpriv->target_pwrs[i]);

	return rc;
}