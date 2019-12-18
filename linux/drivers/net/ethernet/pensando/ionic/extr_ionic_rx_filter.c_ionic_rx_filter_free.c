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
struct ionic_rx_filter {int /*<<< orphan*/  by_hash; int /*<<< orphan*/  by_id; } ;
struct ionic_lif {TYPE_1__* ionic; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  devm_kfree (struct device*,struct ionic_rx_filter*) ; 
 int /*<<< orphan*/  hlist_del (int /*<<< orphan*/ *) ; 

void ionic_rx_filter_free(struct ionic_lif *lif, struct ionic_rx_filter *f)
{
	struct device *dev = lif->ionic->dev;

	hlist_del(&f->by_id);
	hlist_del(&f->by_hash);
	devm_kfree(dev, f);
}