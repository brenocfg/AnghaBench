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
struct talitos_private {int num_channels; int features; scalar_t__ reg_mdeu; scalar_t__ reg; scalar_t__ reg_deu; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TALITOS1_DEUICR_KPE ; 
 int /*<<< orphan*/  TALITOS1_IMR_INIT ; 
 int /*<<< orphan*/  TALITOS1_IMR_LO_INIT ; 
 int /*<<< orphan*/  TALITOS2_IMR_INIT ; 
 int /*<<< orphan*/  TALITOS2_IMR_LO_INIT ; 
 scalar_t__ TALITOS_EUICR ; 
 scalar_t__ TALITOS_EUICR_LO ; 
 int TALITOS_FTR_HW_AUTH_CHECK ; 
 scalar_t__ TALITOS_IMR ; 
 scalar_t__ TALITOS_IMR_LO ; 
 int /*<<< orphan*/  TALITOS_MDEUICR_LO_ICE ; 
 int /*<<< orphan*/  clrbits32 (scalar_t__,int /*<<< orphan*/ ) ; 
 struct talitos_private* dev_get_drvdata (struct device*) ; 
 int has_ftr_sec1 (struct talitos_private*) ; 
 int reset_channel (struct device*,int) ; 
 int reset_device (struct device*) ; 
 int /*<<< orphan*/  setbits32 (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_device(struct device *dev)
{
	struct talitos_private *priv = dev_get_drvdata(dev);
	int ch, err;
	bool is_sec1 = has_ftr_sec1(priv);

	/*
	 * Master reset
	 * errata documentation: warning: certain SEC interrupts
	 * are not fully cleared by writing the MCR:SWR bit,
	 * set bit twice to completely reset
	 */
	err = reset_device(dev);
	if (err)
		return err;

	err = reset_device(dev);
	if (err)
		return err;

	/* reset channels */
	for (ch = 0; ch < priv->num_channels; ch++) {
		err = reset_channel(dev, ch);
		if (err)
			return err;
	}

	/* enable channel done and error interrupts */
	if (is_sec1) {
		clrbits32(priv->reg + TALITOS_IMR, TALITOS1_IMR_INIT);
		clrbits32(priv->reg + TALITOS_IMR_LO, TALITOS1_IMR_LO_INIT);
		/* disable parity error check in DEU (erroneous? test vect.) */
		setbits32(priv->reg_deu + TALITOS_EUICR, TALITOS1_DEUICR_KPE);
	} else {
		setbits32(priv->reg + TALITOS_IMR, TALITOS2_IMR_INIT);
		setbits32(priv->reg + TALITOS_IMR_LO, TALITOS2_IMR_LO_INIT);
	}

	/* disable integrity check error interrupts (use writeback instead) */
	if (priv->features & TALITOS_FTR_HW_AUTH_CHECK)
		setbits32(priv->reg_mdeu + TALITOS_EUICR_LO,
		          TALITOS_MDEUICR_LO_ICE);

	return 0;
}