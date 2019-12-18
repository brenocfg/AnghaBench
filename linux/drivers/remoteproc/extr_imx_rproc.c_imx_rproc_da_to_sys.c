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
typedef  scalar_t__ u64 ;
struct imx_rproc_dcfg {int att_size; struct imx_rproc_att* att; } ;
struct imx_rproc_att {scalar_t__ da; scalar_t__ size; scalar_t__ sa; } ;
struct imx_rproc {int /*<<< orphan*/  dev; struct imx_rproc_dcfg* dcfg; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,scalar_t__,int) ; 

__attribute__((used)) static int imx_rproc_da_to_sys(struct imx_rproc *priv, u64 da,
			       int len, u64 *sys)
{
	const struct imx_rproc_dcfg *dcfg = priv->dcfg;
	int i;

	/* parse address translation table */
	for (i = 0; i < dcfg->att_size; i++) {
		const struct imx_rproc_att *att = &dcfg->att[i];

		if (da >= att->da && da + len < att->da + att->size) {
			unsigned int offset = da - att->da;

			*sys = att->sa + offset;
			return 0;
		}
	}

	dev_warn(priv->dev, "Translation failed: da = 0x%llx len = 0x%x\n",
		 da, len);
	return -ENOENT;
}