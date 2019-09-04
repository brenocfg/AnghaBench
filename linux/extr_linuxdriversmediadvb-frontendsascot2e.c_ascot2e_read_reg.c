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
struct ascot2e_priv {int dummy; } ;

/* Variables and functions */
 int ascot2e_read_regs (struct ascot2e_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ascot2e_read_reg(struct ascot2e_priv *priv, u8 reg, u8 *val)
{
	return ascot2e_read_regs(priv, reg, val, 1);
}