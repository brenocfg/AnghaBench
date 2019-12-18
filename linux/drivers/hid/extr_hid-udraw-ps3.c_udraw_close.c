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
struct udraw {int /*<<< orphan*/  hdev; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hid_hw_close (int /*<<< orphan*/ ) ; 
 struct udraw* input_get_drvdata (struct input_dev*) ; 

__attribute__((used)) static void udraw_close(struct input_dev *dev)
{
	struct udraw *udraw = input_get_drvdata(dev);

	hid_hw_close(udraw->hdev);
}