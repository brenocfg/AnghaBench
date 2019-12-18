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
struct nd_btt {int /*<<< orphan*/  lbasize; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  btt_lbasize_supported ; 
 int /*<<< orphan*/  nd_size_select_show (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 struct nd_btt* to_nd_btt (struct device*) ; 

__attribute__((used)) static ssize_t sector_size_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct nd_btt *nd_btt = to_nd_btt(dev);

	return nd_size_select_show(nd_btt->lbasize, btt_lbasize_supported, buf);
}