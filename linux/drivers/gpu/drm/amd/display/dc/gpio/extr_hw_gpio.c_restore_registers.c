#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  en; int /*<<< orphan*/  a; int /*<<< orphan*/  mask; } ;
struct hw_gpio {TYPE_1__ store; } ;

/* Variables and functions */
 int /*<<< orphan*/  A ; 
 int /*<<< orphan*/  A_reg ; 
 int /*<<< orphan*/  EN ; 
 int /*<<< orphan*/  EN_reg ; 
 int /*<<< orphan*/  MASK ; 
 int /*<<< orphan*/  MASK_reg ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void restore_registers(
	struct hw_gpio *gpio)
{
	REG_UPDATE(MASK_reg, MASK, gpio->store.mask);
	REG_UPDATE(A_reg, A, gpio->store.a);
	REG_UPDATE(EN_reg, EN, gpio->store.en);
	/* TODO restore GPIO_MUX_CONTROL if we ever use it */
}