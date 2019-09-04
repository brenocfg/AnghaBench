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
struct soc_button_data {scalar_t__* children; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int BUTTON_TYPES ; 
 int /*<<< orphan*/  platform_device_unregister (scalar_t__) ; 
 struct soc_button_data* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int soc_button_remove(struct platform_device *pdev)
{
	struct soc_button_data *priv = platform_get_drvdata(pdev);

	int i;

	for (i = 0; i < BUTTON_TYPES; i++)
		if (priv->children[i])
			platform_device_unregister(priv->children[i]);

	return 0;
}