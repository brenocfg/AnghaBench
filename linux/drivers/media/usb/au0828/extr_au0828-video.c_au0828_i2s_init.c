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
struct au0828_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AU0828_AUDIOCTRL_50C ; 
 int /*<<< orphan*/  au0828_writereg (struct au0828_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int au0828_i2s_init(struct au0828_dev *dev)
{
	/* Enable i2s mode */
	au0828_writereg(dev, AU0828_AUDIOCTRL_50C, 0x01);
	return 0;
}