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
typedef  int u8 ;
struct platform_device {int dummy; } ;
struct ocores_i2c {int /*<<< orphan*/  clk; int /*<<< orphan*/  adap; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OCI2C_CONTROL ; 
 int OCI2C_CTRL_EN ; 
 int OCI2C_CTRL_IEN ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 int oc_getreg (struct ocores_i2c*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oc_setreg (struct ocores_i2c*,int /*<<< orphan*/ ,int) ; 
 struct ocores_i2c* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int ocores_i2c_remove(struct platform_device *pdev)
{
	struct ocores_i2c *i2c = platform_get_drvdata(pdev);
	u8 ctrl = oc_getreg(i2c, OCI2C_CONTROL);

	/* disable i2c logic */
	ctrl &= ~(OCI2C_CTRL_EN | OCI2C_CTRL_IEN);
	oc_setreg(i2c, OCI2C_CONTROL, ctrl);

	/* remove adapter & data */
	i2c_del_adapter(&i2c->adap);

	if (!IS_ERR(i2c->clk))
		clk_disable_unprepare(i2c->clk);

	return 0;
}