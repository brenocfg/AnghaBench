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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM365_KEYSCAN ; 
 int davinci_cfg_reg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dm365evm_keyscan_enable(struct device *dev)
{
	return davinci_cfg_reg(DM365_KEYSCAN);
}