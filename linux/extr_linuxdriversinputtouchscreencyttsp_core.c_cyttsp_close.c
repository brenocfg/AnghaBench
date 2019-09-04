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
struct cyttsp {int /*<<< orphan*/  suspended; } ;

/* Variables and functions */
 int /*<<< orphan*/  cyttsp_disable (struct cyttsp*) ; 
 struct cyttsp* input_get_drvdata (struct input_dev*) ; 

__attribute__((used)) static void cyttsp_close(struct input_dev *dev)
{
	struct cyttsp *ts = input_get_drvdata(dev);

	if (!ts->suspended)
		cyttsp_disable(ts);
}