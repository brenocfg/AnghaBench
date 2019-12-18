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
struct snvs_lpgpr_priv {int /*<<< orphan*/  regmap; struct snvs_lpgpr_cfg* dcfg; } ;
struct snvs_lpgpr_cfg {scalar_t__ offset; } ;

/* Variables and functions */
 int regmap_bulk_read (int /*<<< orphan*/ ,scalar_t__,void*,size_t) ; 

__attribute__((used)) static int snvs_lpgpr_read(void *context, unsigned int offset, void *val,
			   size_t bytes)
{
	struct snvs_lpgpr_priv *priv = context;
	const struct snvs_lpgpr_cfg *dcfg = priv->dcfg;

	return regmap_bulk_read(priv->regmap, dcfg->offset + offset,
			       val, bytes / 4);
}