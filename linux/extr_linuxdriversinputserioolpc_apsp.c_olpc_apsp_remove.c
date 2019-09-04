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
struct olpc_apsp {int /*<<< orphan*/  padio; int /*<<< orphan*/  kbio; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct olpc_apsp*) ; 
 struct olpc_apsp* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  serio_unregister_port (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int olpc_apsp_remove(struct platform_device *pdev)
{
	struct olpc_apsp *priv = platform_get_drvdata(pdev);

	free_irq(priv->irq, priv);

	serio_unregister_port(priv->kbio);
	serio_unregister_port(priv->padio);

	return 0;
}