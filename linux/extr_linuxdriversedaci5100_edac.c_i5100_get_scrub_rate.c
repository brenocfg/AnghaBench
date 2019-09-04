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
typedef  int /*<<< orphan*/  u32 ;
struct mem_ctl_info {struct i5100_priv* pvt_info; } ;
struct i5100_priv {int /*<<< orphan*/  mc; } ;

/* Variables and functions */
 int /*<<< orphan*/  I5100_MC ; 
 int i5100_mc_scrben (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int i5100_get_scrub_rate(struct mem_ctl_info *mci)
{
	struct i5100_priv *priv = mci->pvt_info;
	u32 dw;

	pci_read_config_dword(priv->mc, I5100_MC, &dw);

	return 5900000 * i5100_mc_scrben(dw);
}