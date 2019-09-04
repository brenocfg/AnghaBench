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
typedef  int u32 ;
struct talitos_private {scalar_t__ reg; scalar_t__* irq; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int TALITOS1_MCR_SWR ; 
 int TALITOS2_MCR_SWR ; 
 scalar_t__ TALITOS_MCR ; 
 int TALITOS_MCR_RCA1 ; 
 int TALITOS_MCR_RCA3 ; 
 unsigned int TALITOS_TIMEOUT ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct talitos_private* dev_get_drvdata (struct device*) ; 
 int has_ftr_sec1 (struct talitos_private*) ; 
 int in_be32 (scalar_t__) ; 
 int /*<<< orphan*/  setbits32 (scalar_t__,int) ; 

__attribute__((used)) static int reset_device(struct device *dev)
{
	struct talitos_private *priv = dev_get_drvdata(dev);
	unsigned int timeout = TALITOS_TIMEOUT;
	bool is_sec1 = has_ftr_sec1(priv);
	u32 mcr = is_sec1 ? TALITOS1_MCR_SWR : TALITOS2_MCR_SWR;

	setbits32(priv->reg + TALITOS_MCR, mcr);

	while ((in_be32(priv->reg + TALITOS_MCR) & mcr)
	       && --timeout)
		cpu_relax();

	if (priv->irq[1]) {
		mcr = TALITOS_MCR_RCA1 | TALITOS_MCR_RCA3;
		setbits32(priv->reg + TALITOS_MCR, mcr);
	}

	if (timeout == 0) {
		dev_err(dev, "failed to reset device\n");
		return -EIO;
	}

	return 0;
}