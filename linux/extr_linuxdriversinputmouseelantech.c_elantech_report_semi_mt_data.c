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

/* Variables and functions */
 int /*<<< orphan*/  elantech_set_slot (struct input_dev*,int,int,unsigned int,unsigned int) ; 

__attribute__((used)) static void elantech_report_semi_mt_data(struct input_dev *dev,
					 unsigned int num_fingers,
					 unsigned int x1, unsigned int y1,
					 unsigned int x2, unsigned int y2)
{
	elantech_set_slot(dev, 0, num_fingers != 0, x1, y1);
	elantech_set_slot(dev, 1, num_fingers >= 2, x2, y2);
}