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
struct stmpe_touch {int /*<<< orphan*/  stmpe; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  STMPE_BLOCK_TOUCHSCREEN ; 
 struct stmpe_touch* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  stmpe_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stmpe_ts_remove(struct platform_device *pdev)
{
	struct stmpe_touch *ts = platform_get_drvdata(pdev);

	stmpe_disable(ts->stmpe, STMPE_BLOCK_TOUCHSCREEN);

	return 0;
}