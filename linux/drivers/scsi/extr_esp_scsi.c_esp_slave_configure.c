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
struct scsi_device {size_t id; int /*<<< orphan*/  sdev_target; scalar_t__ tagged_supported; int /*<<< orphan*/  host; } ;
struct esp_target_data {int /*<<< orphan*/  flags; } ;
struct esp {int /*<<< orphan*/  num_tags; struct esp_target_data* target; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_TGT_DISCONNECT ; 
 int /*<<< orphan*/  scsi_change_queue_depth (struct scsi_device*,int /*<<< orphan*/ ) ; 
 struct esp* shost_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_dv_device (struct scsi_device*) ; 
 int /*<<< orphan*/  spi_initial_dv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int esp_slave_configure(struct scsi_device *dev)
{
	struct esp *esp = shost_priv(dev->host);
	struct esp_target_data *tp = &esp->target[dev->id];

	if (dev->tagged_supported)
		scsi_change_queue_depth(dev, esp->num_tags);

	tp->flags |= ESP_TGT_DISCONNECT;

	if (!spi_initial_dv(dev->sdev_target))
		spi_dv_device(dev);

	return 0;
}