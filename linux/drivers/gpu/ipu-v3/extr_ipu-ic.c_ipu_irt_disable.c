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
struct ipu_ic_priv {int /*<<< orphan*/  ipu; scalar_t__ irt_use_count; } ;
struct ipu_ic {struct ipu_ic_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPU_CONF_ROT_EN ; 
 int /*<<< orphan*/  ipu_module_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ipu_irt_disable(struct ipu_ic *ic)
{
	struct ipu_ic_priv *priv = ic->priv;

	if (priv->irt_use_count) {
		if (!--priv->irt_use_count)
			ipu_module_disable(priv->ipu, IPU_CONF_ROT_EN);
	}
}