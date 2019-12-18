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
struct kxtj9_data {int dummy; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 struct kxtj9_data* input_get_drvdata (struct input_dev*) ; 
 int kxtj9_enable (struct kxtj9_data*) ; 

__attribute__((used)) static int kxtj9_input_open(struct input_dev *input)
{
	struct kxtj9_data *tj9 = input_get_drvdata(input);

	return kxtj9_enable(tj9);
}