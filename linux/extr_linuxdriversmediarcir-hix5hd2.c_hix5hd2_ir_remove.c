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
struct platform_device {int dummy; } ;
struct hix5hd2_ir_priv {int /*<<< orphan*/  rdev; int /*<<< orphan*/  clock; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct hix5hd2_ir_priv* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  rc_unregister_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hix5hd2_ir_remove(struct platform_device *pdev)
{
	struct hix5hd2_ir_priv *priv = platform_get_drvdata(pdev);

	clk_disable_unprepare(priv->clock);
	rc_unregister_device(priv->rdev);
	return 0;
}