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
struct device {int dummy; } ;
struct ata_port_operations {int dummy; } ;
struct ata_host {int /*<<< orphan*/  kref; struct ata_port_operations* ops; struct device* dev; int /*<<< orphan*/  n_tags; int /*<<< orphan*/  eh_mutex; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_MAX_QUEUE ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void ata_host_init(struct ata_host *host, struct device *dev,
		   struct ata_port_operations *ops)
{
	spin_lock_init(&host->lock);
	mutex_init(&host->eh_mutex);
	host->n_tags = ATA_MAX_QUEUE;
	host->dev = dev;
	host->ops = ops;
	kref_init(&host->kref);
}