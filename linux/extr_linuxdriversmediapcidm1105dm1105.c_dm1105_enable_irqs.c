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
struct dm1105_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM1105_CR ; 
 int /*<<< orphan*/  DM1105_INTMAK ; 
 int INTMAK_ALLMASK ; 
 int /*<<< orphan*/  dm_writeb (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dm1105_enable_irqs(struct dm1105_dev *dev)
{
	dm_writeb(DM1105_INTMAK, INTMAK_ALLMASK);
	dm_writeb(DM1105_CR, 1);
}