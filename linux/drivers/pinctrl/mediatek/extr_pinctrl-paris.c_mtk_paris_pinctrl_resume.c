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
struct mtk_pinctrl {int /*<<< orphan*/  eint; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct mtk_pinctrl* dev_get_drvdata (struct device*) ; 
 int mtk_eint_do_resume (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtk_paris_pinctrl_resume(struct device *device)
{
	struct mtk_pinctrl *pctl = dev_get_drvdata(device);

	return mtk_eint_do_resume(pctl->eint);
}