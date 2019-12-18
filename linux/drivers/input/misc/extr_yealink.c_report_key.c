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
struct yealink_dev {int key_code; struct input_dev* idev; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_report_key (struct input_dev*,int,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 

__attribute__((used)) static void report_key(struct yealink_dev *yld, int key)
{
	struct input_dev *idev = yld->idev;

	if (yld->key_code >= 0) {
		/* old key up */
		input_report_key(idev, yld->key_code & 0xff, 0);
		if (yld->key_code >> 8)
			input_report_key(idev, yld->key_code >> 8, 0);
	}

	yld->key_code = key;
	if (key >= 0) {
		/* new valid key */
		input_report_key(idev, key & 0xff, 1);
		if (key >> 8)
			input_report_key(idev, key >> 8, 1);
	}
	input_sync(idev);
}