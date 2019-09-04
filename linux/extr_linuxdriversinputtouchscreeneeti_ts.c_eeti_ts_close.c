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
struct eeti_ts {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  eeti_ts_stop (struct eeti_ts*) ; 
 struct eeti_ts* input_get_drvdata (struct input_dev*) ; 

__attribute__((used)) static void eeti_ts_close(struct input_dev *dev)
{
	struct eeti_ts *eeti = input_get_drvdata(dev);

	eeti_ts_stop(eeti);
}