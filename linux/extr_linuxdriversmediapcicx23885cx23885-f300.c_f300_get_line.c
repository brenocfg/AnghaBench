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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct cx23885_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cx23885_gpio_enable (struct cx23885_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx23885_gpio_get (struct cx23885_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 f300_get_line(struct cx23885_dev *dev, u32 line)
{
	cx23885_gpio_enable(dev, line, 0);

	return cx23885_gpio_get(dev, line);
}