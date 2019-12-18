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
struct ipu_soc {struct ipu_prg* prg_priv; } ;
struct ipu_prg {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 

int ipu_prg_enable(struct ipu_soc *ipu)
{
	struct ipu_prg *prg = ipu->prg_priv;

	if (!prg)
		return 0;

	return pm_runtime_get_sync(prg->dev);
}