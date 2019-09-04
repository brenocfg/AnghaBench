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
struct ams_delta_serio {int /*<<< orphan*/  serio; } ;

/* Variables and functions */
 struct ams_delta_serio* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  serio_unregister_port (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ams_delta_serio_exit(struct platform_device *pdev)
{
	struct ams_delta_serio *priv = platform_get_drvdata(pdev);

	serio_unregister_port(priv->serio);

	return 0;
}