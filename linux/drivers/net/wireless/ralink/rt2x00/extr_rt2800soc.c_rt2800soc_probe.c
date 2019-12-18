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
 int /*<<< orphan*/  rt2800soc_ops ; 
 int rt2x00soc_probe (struct platform_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rt2800soc_probe(struct platform_device *pdev)
{
	return rt2x00soc_probe(pdev, &rt2800soc_ops);
}