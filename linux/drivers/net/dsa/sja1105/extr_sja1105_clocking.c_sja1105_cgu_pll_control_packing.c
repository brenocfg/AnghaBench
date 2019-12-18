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
struct sja1105_cgu_pll_ctrl {int /*<<< orphan*/  pd; int /*<<< orphan*/  bypass; int /*<<< orphan*/  fbsel; int /*<<< orphan*/  direct; int /*<<< orphan*/  psel; int /*<<< orphan*/  autoblock; int /*<<< orphan*/  msel; int /*<<< orphan*/  pllclksrc; } ;
typedef  enum packing_op { ____Placeholder_packing_op } packing_op ;

/* Variables and functions */
 int /*<<< orphan*/  sja1105_packing (void*,int /*<<< orphan*/ *,int,int,int const,int) ; 

__attribute__((used)) static void
sja1105_cgu_pll_control_packing(void *buf, struct sja1105_cgu_pll_ctrl *cmd,
				enum packing_op op)
{
	const int size = 4;

	sja1105_packing(buf, &cmd->pllclksrc, 28, 24, size, op);
	sja1105_packing(buf, &cmd->msel,      23, 16, size, op);
	sja1105_packing(buf, &cmd->autoblock, 11, 11, size, op);
	sja1105_packing(buf, &cmd->psel,       9,  8, size, op);
	sja1105_packing(buf, &cmd->direct,     7,  7, size, op);
	sja1105_packing(buf, &cmd->fbsel,      6,  6, size, op);
	sja1105_packing(buf, &cmd->bypass,     1,  1, size, op);
	sja1105_packing(buf, &cmd->pd,         0,  0, size, op);
}