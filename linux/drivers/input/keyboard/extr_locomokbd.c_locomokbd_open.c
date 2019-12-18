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
typedef  int u16 ;
struct locomokbd {scalar_t__ base; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ LOCOMO_KIC ; 
 struct locomokbd* input_get_drvdata (struct input_dev*) ; 
 int locomo_readl (scalar_t__) ; 
 int /*<<< orphan*/  locomo_writel (int,scalar_t__) ; 

__attribute__((used)) static int locomokbd_open(struct input_dev *dev)
{
	struct locomokbd *locomokbd = input_get_drvdata(dev);
	u16 r;
	
	r = locomo_readl(locomokbd->base + LOCOMO_KIC) | 0x0010;
	locomo_writel(r, locomokbd->base + LOCOMO_KIC);
	return 0;
}