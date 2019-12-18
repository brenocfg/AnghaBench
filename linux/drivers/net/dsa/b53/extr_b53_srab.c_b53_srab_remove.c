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
struct b53_srab_priv {int dummy; } ;
struct b53_device {struct b53_srab_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  b53_srab_intr_set (struct b53_srab_priv*,int) ; 
 int /*<<< orphan*/  b53_switch_remove (struct b53_device*) ; 
 struct b53_device* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int b53_srab_remove(struct platform_device *pdev)
{
	struct b53_device *dev = platform_get_drvdata(pdev);
	struct b53_srab_priv *priv = dev->priv;

	b53_srab_intr_set(priv, false);
	if (dev)
		b53_switch_remove(dev);

	return 0;
}