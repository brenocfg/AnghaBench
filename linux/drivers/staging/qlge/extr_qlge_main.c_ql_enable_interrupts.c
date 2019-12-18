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
struct ql_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTR_EN ; 
 int INTR_EN_EI ; 
 int /*<<< orphan*/  ql_write32 (struct ql_adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ql_enable_interrupts(struct ql_adapter *qdev)
{
	ql_write32(qdev, INTR_EN, (INTR_EN_EI << 16) | INTR_EN_EI);
}