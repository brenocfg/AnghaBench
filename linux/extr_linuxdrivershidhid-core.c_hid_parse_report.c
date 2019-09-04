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
struct hid_device {unsigned int dev_rsize; int /*<<< orphan*/  dev_rdesc; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kmemdup (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 

int hid_parse_report(struct hid_device *hid, __u8 *start, unsigned size)
{
	hid->dev_rdesc = kmemdup(start, size, GFP_KERNEL);
	if (!hid->dev_rdesc)
		return -ENOMEM;
	hid->dev_rsize = size;
	return 0;
}