#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct st_modedef {TYPE_2__* tape; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_4__ {TYPE_1__* stats; } ;
struct TYPE_3__ {int /*<<< orphan*/  write_byte_cnt; } ;

/* Variables and functions */
 scalar_t__ atomic64_read (int /*<<< orphan*/ *) ; 
 struct st_modedef* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,long long) ; 

__attribute__((used)) static ssize_t write_byte_cnt_show(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	struct st_modedef *STm = dev_get_drvdata(dev);

	return sprintf(buf, "%lld",
		       (long long)atomic64_read(&STm->tape->stats->write_byte_cnt));
}