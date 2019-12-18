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
struct mc13xxx_regulator_priv {int powermisc_pwgt_state; struct mc13xxx* mc13xxx; } ;
struct mc13xxx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  MC13783_REG_POWERMISC ; 
 int MC13783_REG_POWERMISC_PWGTSPI_M ; 
 int /*<<< orphan*/  mc13xxx_lock (struct mc13xxx*) ; 
 int mc13xxx_reg_read (struct mc13xxx*,int /*<<< orphan*/ ,int*) ; 
 int mc13xxx_reg_write (struct mc13xxx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mc13xxx_unlock (struct mc13xxx*) ; 

__attribute__((used)) static int mc13783_powermisc_rmw(struct mc13xxx_regulator_priv *priv, u32 mask,
		u32 val)
{
	struct mc13xxx *mc13783 = priv->mc13xxx;
	int ret;
	u32 valread;

	BUG_ON(val & ~mask);

	mc13xxx_lock(priv->mc13xxx);
	ret = mc13xxx_reg_read(mc13783, MC13783_REG_POWERMISC, &valread);
	if (ret)
		goto out;

	/* Update the stored state for Power Gates. */
	priv->powermisc_pwgt_state =
				(priv->powermisc_pwgt_state & ~mask) | val;
	priv->powermisc_pwgt_state &= MC13783_REG_POWERMISC_PWGTSPI_M;

	/* Construct the new register value */
	valread = (valread & ~mask) | val;
	/* Overwrite the PWGTxEN with the stored version */
	valread = (valread & ~MC13783_REG_POWERMISC_PWGTSPI_M) |
						priv->powermisc_pwgt_state;

	ret = mc13xxx_reg_write(mc13783, MC13783_REG_POWERMISC, valread);
out:
	mc13xxx_unlock(priv->mc13xxx);
	return ret;
}