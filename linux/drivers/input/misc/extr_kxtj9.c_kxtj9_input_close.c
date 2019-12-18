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
 int /*<<< orphan*/  kxtj9_disable (struct kxtj9_data*) ; 

__attribute__((used)) static void kxtj9_input_close(struct input_dev *dev)
{
	struct kxtj9_data *tj9 = input_get_drvdata(dev);

	kxtj9_disable(tj9);
}