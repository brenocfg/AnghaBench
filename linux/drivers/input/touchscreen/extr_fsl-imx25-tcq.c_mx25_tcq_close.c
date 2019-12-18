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
struct mx25_tcq_priv {int /*<<< orphan*/  clk; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct mx25_tcq_priv* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  mx25_tcq_disable_fifo_irq (struct mx25_tcq_priv*) ; 
 int /*<<< orphan*/  mx25_tcq_disable_touch_irq (struct mx25_tcq_priv*) ; 
 int /*<<< orphan*/  mx25_tcq_force_queue_stop (struct mx25_tcq_priv*) ; 

__attribute__((used)) static void mx25_tcq_close(struct input_dev *idev)
{
	struct mx25_tcq_priv *priv = input_get_drvdata(idev);

	mx25_tcq_force_queue_stop(priv);
	mx25_tcq_disable_touch_irq(priv);
	mx25_tcq_disable_fifo_irq(priv);
	clk_disable_unprepare(priv->clk);
}