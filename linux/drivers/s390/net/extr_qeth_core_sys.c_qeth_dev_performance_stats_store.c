#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct qeth_qdio_out_q {int /*<<< orphan*/  stats; } ;
struct TYPE_2__ {unsigned int no_out_queues; struct qeth_qdio_out_q** out_qs; } ;
struct qeth_card {TYPE_1__ qdio; int /*<<< orphan*/  stats; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 struct qeth_card* dev_get_drvdata (struct device*) ; 
 int kstrtobool (char const*,int*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ssize_t qeth_dev_performance_stats_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	struct qeth_card *card = dev_get_drvdata(dev);
	struct qeth_qdio_out_q *queue;
	unsigned int i;
	bool reset;
	int rc;

	if (!card)
		return -EINVAL;

	rc = kstrtobool(buf, &reset);
	if (rc)
		return rc;

	if (reset) {
		memset(&card->stats, 0, sizeof(card->stats));
		for (i = 0; i < card->qdio.no_out_queues; i++) {
			queue = card->qdio.out_qs[i];
			if (!queue)
				break;
			memset(&queue->stats, 0, sizeof(queue->stats));
		}
	}

	return count;
}