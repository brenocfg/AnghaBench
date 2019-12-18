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
struct tps6586x {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  __remove_subdev ; 
 int device_for_each_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tps6586x_remove_subdevs(struct tps6586x *tps6586x)
{
	return device_for_each_child(tps6586x->dev, NULL, __remove_subdev);
}