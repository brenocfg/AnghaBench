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
typedef  int /*<<< orphan*/  u8 ;
struct helene_priv {int dummy; } ;

/* Variables and functions */
 int helene_write_regs (struct helene_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int helene_write_reg(struct helene_priv *priv, u8 reg, u8 val)
{
	u8 tmp = val; /* see gcc.gnu.org/bugzilla/show_bug.cgi?id=81715 */

	return helene_write_regs(priv, reg, &tmp, 1);
}