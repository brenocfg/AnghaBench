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
struct mc13783_adc_priv {int /*<<< orphan*/  mc13xxx; } ;

/* Variables and functions */
 unsigned int MC13XXX_USE_TOUCHSCREEN ; 
 unsigned int mc13xxx_get_flags (int /*<<< orphan*/ ) ; 
 struct mc13783_adc_priv* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int mc13783_adc_use_touchscreen(struct platform_device *pdev)
{
	struct mc13783_adc_priv *priv = platform_get_drvdata(pdev);
	unsigned flags = mc13xxx_get_flags(priv->mc13xxx);

	return flags & MC13XXX_USE_TOUCHSCREEN;
}