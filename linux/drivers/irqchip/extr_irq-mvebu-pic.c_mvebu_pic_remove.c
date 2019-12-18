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
struct mvebu_pic {int /*<<< orphan*/  domain; } ;

/* Variables and functions */
 int /*<<< orphan*/  irq_domain_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvebu_pic_disable_percpu_irq ; 
 int /*<<< orphan*/  on_each_cpu (int /*<<< orphan*/ ,struct mvebu_pic*,int) ; 
 struct mvebu_pic* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int mvebu_pic_remove(struct platform_device *pdev)
{
	struct mvebu_pic *pic = platform_get_drvdata(pdev);

	on_each_cpu(mvebu_pic_disable_percpu_irq, pic, 1);
	irq_domain_remove(pic->domain);

	return 0;
}