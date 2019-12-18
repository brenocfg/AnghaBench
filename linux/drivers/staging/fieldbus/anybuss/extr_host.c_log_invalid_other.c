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
typedef  int /*<<< orphan*/  u16 ;
struct device {int dummy; } ;
struct anybus_mbox_hdr {int /*<<< orphan*/ * extended; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void log_invalid_other(struct device *dev,
			      struct anybus_mbox_hdr *hdr)
{
	size_t ext_offs = ARRAY_SIZE(hdr->extended) - 1;
	u16 code = be16_to_cpu(hdr->extended[ext_offs]);

	dev_err(dev, "   Invalid other: [0x%02X]", code);
}