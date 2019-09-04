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
struct apbps2_priv {int /*<<< orphan*/  io; } ;

/* Variables and functions */
 struct apbps2_priv* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  serio_unregister_port (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int apbps2_of_remove(struct platform_device *of_dev)
{
	struct apbps2_priv *priv = platform_get_drvdata(of_dev);

	serio_unregister_port(priv->io);

	return 0;
}