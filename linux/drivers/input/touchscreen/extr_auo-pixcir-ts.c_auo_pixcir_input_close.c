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
struct auo_pixcir_ts {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  auo_pixcir_stop (struct auo_pixcir_ts*) ; 
 struct auo_pixcir_ts* input_get_drvdata (struct input_dev*) ; 

__attribute__((used)) static void auo_pixcir_input_close(struct input_dev *dev)
{
	struct auo_pixcir_ts *ts = input_get_drvdata(dev);

	auo_pixcir_stop(ts);
}