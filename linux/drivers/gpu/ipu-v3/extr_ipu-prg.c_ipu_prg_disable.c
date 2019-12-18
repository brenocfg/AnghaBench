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
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 

void ipu_prg_disable(struct ipu_soc *ipu)
{
	struct ipu_prg *prg = ipu->prg_priv;

	if (!prg)
		return;

	pm_runtime_put(prg->dev);
}