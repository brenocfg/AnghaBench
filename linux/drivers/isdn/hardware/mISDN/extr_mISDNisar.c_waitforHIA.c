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
struct isar_hw {int (* read_reg ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  name; int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISAR_HIA ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static inline int
waitforHIA(struct isar_hw *isar, int timeout)
{
	int t = timeout;
	u8 val = isar->read_reg(isar->hw, ISAR_HIA);

	while ((val & 1) && t) {
		udelay(1);
		t--;
		val = isar->read_reg(isar->hw, ISAR_HIA);
	}
	pr_debug("%s: HIA after %dus\n", isar->name, timeout - t);
	return timeout;
}