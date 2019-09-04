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
struct device {int dummy; } ;
struct bcmgenet_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_get_drvdata (struct device*) ; 
 struct bcmgenet_priv* netdev_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct bcmgenet_priv *dev_to_priv(struct device *dev)
{
	return netdev_priv(dev_get_drvdata(dev));
}