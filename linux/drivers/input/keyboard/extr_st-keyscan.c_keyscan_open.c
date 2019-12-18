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
struct st_keyscan {int dummy; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 struct st_keyscan* input_get_drvdata (struct input_dev*) ; 
 int keyscan_start (struct st_keyscan*) ; 

__attribute__((used)) static int keyscan_open(struct input_dev *dev)
{
	struct st_keyscan *keypad = input_get_drvdata(dev);

	return keyscan_start(keypad);
}