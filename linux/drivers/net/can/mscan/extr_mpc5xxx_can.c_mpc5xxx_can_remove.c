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
struct of_device_id {struct mpc5xxx_can_data* data; } ;
struct net_device {int /*<<< orphan*/  irq; } ;
struct mscan_priv {int /*<<< orphan*/  reg_base; } ;
struct mpc5xxx_can_data {int /*<<< orphan*/  (* put_clock ) (struct platform_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  free_candev (struct net_device*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_dispose_mapping (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpc5xxx_can_table ; 
 struct mscan_priv* netdev_priv (struct net_device*) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct net_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  stub1 (struct platform_device*) ; 
 int /*<<< orphan*/  unregister_mscandev (struct net_device*) ; 

__attribute__((used)) static int mpc5xxx_can_remove(struct platform_device *ofdev)
{
	const struct of_device_id *match;
	const struct mpc5xxx_can_data *data;
	struct net_device *dev = platform_get_drvdata(ofdev);
	struct mscan_priv *priv = netdev_priv(dev);

	match = of_match_device(mpc5xxx_can_table, &ofdev->dev);
	data = match ? match->data : NULL;

	unregister_mscandev(dev);
	if (data && data->put_clock)
		data->put_clock(ofdev);
	iounmap(priv->reg_base);
	irq_dispose_mapping(dev->irq);
	free_candev(dev);

	return 0;
}