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
struct bma150_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bma150_close (struct bma150_data*) ; 
 struct bma150_data* input_get_drvdata (struct input_dev*) ; 

__attribute__((used)) static void bma150_irq_close(struct input_dev *input)
{
	struct bma150_data *bma150 = input_get_drvdata(input);

	bma150_close(bma150);
}