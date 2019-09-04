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
struct hid_device {int dummy; } ;
struct appleir {int /*<<< orphan*/  input_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void key_down(struct hid_device *hid, struct appleir *appleir, int key)
{
	input_report_key(appleir->input_dev, key, 1);
	input_sync(appleir->input_dev);
}