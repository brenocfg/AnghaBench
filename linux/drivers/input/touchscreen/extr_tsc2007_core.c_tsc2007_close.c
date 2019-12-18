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
struct tsc2007 {int dummy; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 struct tsc2007* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  tsc2007_stop (struct tsc2007*) ; 

__attribute__((used)) static void tsc2007_close(struct input_dev *input_dev)
{
	struct tsc2007 *ts = input_get_drvdata(input_dev);

	tsc2007_stop(ts);
}