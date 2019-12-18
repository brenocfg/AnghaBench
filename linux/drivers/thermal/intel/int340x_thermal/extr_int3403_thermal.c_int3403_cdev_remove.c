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
struct int3403_priv {struct int3403_cdev* priv; } ;
struct int3403_cdev {int /*<<< orphan*/  cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  thermal_cooling_device_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int int3403_cdev_remove(struct int3403_priv *priv)
{
	struct int3403_cdev *obj = priv->priv;

	thermal_cooling_device_unregister(obj->cdev);
	return 0;
}