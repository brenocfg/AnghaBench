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
typedef  int /*<<< orphan*/  u32 ;
struct qca8k_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  qca8k_rmw (struct qca8k_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
qca8k_reg_clear(struct qca8k_priv *priv, u32 reg, u32 val)
{
	qca8k_rmw(priv, reg, val, 0);
}