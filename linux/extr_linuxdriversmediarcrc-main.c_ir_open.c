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
struct rc_dev {int dummy; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 struct rc_dev* input_get_drvdata (struct input_dev*) ; 
 int rc_open (struct rc_dev*) ; 

__attribute__((used)) static int ir_open(struct input_dev *idev)
{
	struct rc_dev *rdev = input_get_drvdata(idev);

	return rc_open(rdev);
}