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
struct scsi_cmnd {TYPE_1__* device; } ;
struct esp {TYPE_2__* host; } ;
struct TYPE_4__ {int /*<<< orphan*/  host_lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int SUCCESS ; 
 int /*<<< orphan*/  esp_bootup_reset (struct esp*) ; 
 int /*<<< orphan*/  esp_bus_reset_settle ; 
 int /*<<< orphan*/  esp_reset_cleanup (struct esp*) ; 
 struct esp* shost_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  ssleep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int esp_eh_host_reset_handler(struct scsi_cmnd *cmd)
{
	struct esp *esp = shost_priv(cmd->device->host);
	unsigned long flags;

	spin_lock_irqsave(esp->host->host_lock, flags);
	esp_bootup_reset(esp);
	esp_reset_cleanup(esp);
	spin_unlock_irqrestore(esp->host->host_lock, flags);

	ssleep(esp_bus_reset_settle);

	return SUCCESS;
}