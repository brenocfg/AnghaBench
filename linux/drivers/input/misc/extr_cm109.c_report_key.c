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
struct cm109_dev {int key_code; struct input_dev* idev; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_report_key (struct input_dev*,int,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 

__attribute__((used)) static void report_key(struct cm109_dev *dev, int key)
{
	struct input_dev *idev = dev->idev;

	if (dev->key_code >= 0) {
		/* old key up */
		input_report_key(idev, dev->key_code, 0);
	}

	dev->key_code = key;
	if (key >= 0) {
		/* new valid key */
		input_report_key(idev, key, 1);
	}

	input_sync(idev);
}