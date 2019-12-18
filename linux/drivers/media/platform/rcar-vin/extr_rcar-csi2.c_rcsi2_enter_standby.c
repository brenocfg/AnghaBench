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
struct rcar_csi2 {int /*<<< orphan*/  dev; int /*<<< orphan*/  rstc; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHTC_REG ; 
 int /*<<< orphan*/  PHTC_TESTCLR ; 
 int /*<<< orphan*/  PHYCNT_REG ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcsi2_write (struct rcar_csi2*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void rcsi2_enter_standby(struct rcar_csi2 *priv)
{
	rcsi2_write(priv, PHYCNT_REG, 0);
	rcsi2_write(priv, PHTC_REG, PHTC_TESTCLR);
	reset_control_assert(priv->rstc);
	usleep_range(100, 150);
	pm_runtime_put(priv->dev);
}