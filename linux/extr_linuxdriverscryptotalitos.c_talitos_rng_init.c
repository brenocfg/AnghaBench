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
struct talitos_private {scalar_t__ reg_rngu; } ;
struct hwrng {scalar_t__ priv; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ TALITOS_EUDSR_LO ; 
 scalar_t__ TALITOS_EURCR_LO ; 
 scalar_t__ TALITOS_EUSR_LO ; 
 int /*<<< orphan*/  TALITOS_RNGURCR_LO_SR ; 
 int TALITOS_RNGUSR_LO_RD ; 
 unsigned int TALITOS_TIMEOUT ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct talitos_private* dev_get_drvdata (struct device*) ; 
 int in_be32 (scalar_t__) ; 
 int /*<<< orphan*/  setbits32 (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int talitos_rng_init(struct hwrng *rng)
{
	struct device *dev = (struct device *)rng->priv;
	struct talitos_private *priv = dev_get_drvdata(dev);
	unsigned int timeout = TALITOS_TIMEOUT;

	setbits32(priv->reg_rngu + TALITOS_EURCR_LO, TALITOS_RNGURCR_LO_SR);
	while (!(in_be32(priv->reg_rngu + TALITOS_EUSR_LO)
		 & TALITOS_RNGUSR_LO_RD)
	       && --timeout)
		cpu_relax();
	if (timeout == 0) {
		dev_err(dev, "failed to reset rng hw\n");
		return -ENODEV;
	}

	/* start generating */
	setbits32(priv->reg_rngu + TALITOS_EUDSR_LO, 0);

	return 0;
}