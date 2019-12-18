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
struct TYPE_3__ {int /*<<< orphan*/  time_total; } ;
struct TYPE_4__ {TYPE_1__ blkt; } ;
struct qeth_card {TYPE_2__ info; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct qeth_card* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  qeth_dev_blkt_store (struct qeth_card*,char const*,size_t,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static ssize_t qeth_dev_blkt_total_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	struct qeth_card *card = dev_get_drvdata(dev);

	return qeth_dev_blkt_store(card, buf, count,
				   &card->info.blkt.time_total, 5000);
}