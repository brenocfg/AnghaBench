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
struct pxa930_rotary {int dummy; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_sbcr (struct pxa930_rotary*) ; 
 struct pxa930_rotary* input_get_drvdata (struct input_dev*) ; 

__attribute__((used)) static int pxa930_rotary_open(struct input_dev *dev)
{
	struct pxa930_rotary *r = input_get_drvdata(dev);

	clear_sbcr(r);

	return 0;
}