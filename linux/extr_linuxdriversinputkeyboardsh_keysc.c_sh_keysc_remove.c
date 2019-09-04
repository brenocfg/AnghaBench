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
struct sh_keysc_priv {int /*<<< orphan*/  iomem_base; int /*<<< orphan*/  input; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  KYCR2 ; 
 int /*<<< orphan*/  KYCR2_IRQ_DISABLED ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct platform_device*) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct sh_keysc_priv*) ; 
 struct sh_keysc_priv* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sh_keysc_write (struct sh_keysc_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sh_keysc_remove(struct platform_device *pdev)
{
	struct sh_keysc_priv *priv = platform_get_drvdata(pdev);

	sh_keysc_write(priv, KYCR2, KYCR2_IRQ_DISABLED);

	input_unregister_device(priv->input);
	free_irq(platform_get_irq(pdev, 0), pdev);
	iounmap(priv->iomem_base);

	pm_runtime_put_sync(&pdev->dev);
	pm_runtime_disable(&pdev->dev);

	kfree(priv);

	return 0;
}