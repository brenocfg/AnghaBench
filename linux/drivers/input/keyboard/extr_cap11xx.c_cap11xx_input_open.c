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
struct input_dev {int dummy; } ;
struct cap11xx_priv {int dummy; } ;

/* Variables and functions */
 int cap11xx_set_sleep (struct cap11xx_priv*,int) ; 
 struct cap11xx_priv* input_get_drvdata (struct input_dev*) ; 

__attribute__((used)) static int cap11xx_input_open(struct input_dev *idev)
{
	struct cap11xx_priv *priv = input_get_drvdata(idev);

	return cap11xx_set_sleep(priv, false);
}