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
struct stmpe {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  STMPE_FIFO_STA_RESET ; 
 int /*<<< orphan*/  STMPE_REG_FIFO_STA ; 
 int stmpe_set_bits (struct stmpe*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __stmpe_reset_fifo(struct stmpe *stmpe)
{
	int ret;

	ret = stmpe_set_bits(stmpe, STMPE_REG_FIFO_STA,
			STMPE_FIFO_STA_RESET, STMPE_FIFO_STA_RESET);
	if (ret)
		return ret;

	return stmpe_set_bits(stmpe, STMPE_REG_FIFO_STA,
			STMPE_FIFO_STA_RESET, 0);
}