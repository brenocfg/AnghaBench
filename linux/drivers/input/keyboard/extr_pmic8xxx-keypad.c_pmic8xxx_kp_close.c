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
struct pmic8xxx_kp {int dummy; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 struct pmic8xxx_kp* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  pmic8xxx_kp_disable (struct pmic8xxx_kp*) ; 

__attribute__((used)) static void pmic8xxx_kp_close(struct input_dev *dev)
{
	struct pmic8xxx_kp *kp = input_get_drvdata(dev);

	pmic8xxx_kp_disable(kp);
}