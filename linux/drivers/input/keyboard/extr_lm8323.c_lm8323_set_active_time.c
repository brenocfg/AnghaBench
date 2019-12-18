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
struct lm8323_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LM8323_CMD_SET_ACTIVE ; 
 int /*<<< orphan*/  lm8323_write (struct lm8323_chip*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void lm8323_set_active_time(struct lm8323_chip *lm, int time)
{
	lm8323_write(lm, 2, LM8323_CMD_SET_ACTIVE, time >> 2);
}