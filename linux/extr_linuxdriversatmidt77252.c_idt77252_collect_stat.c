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
struct idt77252_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAR_REG_CDC ; 
 int /*<<< orphan*/  SAR_REG_ICC ; 
 int /*<<< orphan*/  SAR_REG_VPEC ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
idt77252_collect_stat(struct idt77252_dev *card)
{
	(void) readl(SAR_REG_CDC);
	(void) readl(SAR_REG_VPEC);
	(void) readl(SAR_REG_ICC);

}