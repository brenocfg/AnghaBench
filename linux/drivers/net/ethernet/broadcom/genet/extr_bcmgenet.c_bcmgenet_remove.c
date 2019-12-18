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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct bcmgenet_priv {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcmgenet_mii_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct bcmgenet_priv* dev_to_priv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_netdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_netdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcmgenet_remove(struct platform_device *pdev)
{
	struct bcmgenet_priv *priv = dev_to_priv(&pdev->dev);

	dev_set_drvdata(&pdev->dev, NULL);
	unregister_netdev(priv->dev);
	bcmgenet_mii_exit(priv->dev);
	free_netdev(priv->dev);

	return 0;
}