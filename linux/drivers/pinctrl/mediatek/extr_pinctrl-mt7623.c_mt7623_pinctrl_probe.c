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

/* Variables and functions */
 int /*<<< orphan*/  mt7623_bonding_disable (struct platform_device*) ; 
 int /*<<< orphan*/  mt7623_data ; 
 int mtk_moore_pinctrl_probe (struct platform_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mt7623_pinctrl_probe(struct platform_device *pdev)
{
	int err;

	err = mtk_moore_pinctrl_probe(pdev, &mt7623_data);
	if (err)
		return err;

	mt7623_bonding_disable(pdev);

	return 0;
}