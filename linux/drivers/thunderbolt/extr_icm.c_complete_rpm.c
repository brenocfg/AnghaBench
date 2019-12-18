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
struct tb_switch {int /*<<< orphan*/  rpm_complete; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 struct tb_switch* tb_to_switch (struct device*) ; 

__attribute__((used)) static int complete_rpm(struct device *dev, void *data)
{
	struct tb_switch *sw = tb_to_switch(dev);

	if (sw)
		complete(&sw->rpm_complete);
	return 0;
}