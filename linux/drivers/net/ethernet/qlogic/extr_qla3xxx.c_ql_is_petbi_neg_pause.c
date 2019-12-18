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
typedef  int u16 ;
struct ql3_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PETBI_NEG_PARTNER ; 
 int PETBI_NEG_PAUSE ; 
 int PETBI_NEG_PAUSE_MASK ; 
 scalar_t__ ql_mii_read_reg (struct ql3_adapter*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int ql_is_petbi_neg_pause(struct ql3_adapter *qdev)
{
	u16 reg;

	if (ql_mii_read_reg(qdev, PETBI_NEG_PARTNER, &reg) < 0)
		return 0;

	return (reg & PETBI_NEG_PAUSE_MASK) == PETBI_NEG_PAUSE;
}