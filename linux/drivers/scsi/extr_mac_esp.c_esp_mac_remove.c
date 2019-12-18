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
struct platform_device {size_t id; } ;
struct mac_esp_priv {struct esp* esp; } ;
struct esp {TYPE_1__* host; struct mac_esp_priv* command_block; } ;
struct TYPE_2__ {unsigned int irq; } ;

/* Variables and functions */
 int /*<<< orphan*/ ** esp_chips ; 
 int /*<<< orphan*/  esp_chips_lock ; 
 int /*<<< orphan*/  free_irq (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct mac_esp_priv*) ; 
 struct mac_esp_priv* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  scsi_esp_unregister (struct esp*) ; 
 int /*<<< orphan*/  scsi_host_put (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int esp_mac_remove(struct platform_device *dev)
{
	struct mac_esp_priv *mep = platform_get_drvdata(dev);
	struct esp *esp = mep->esp;
	unsigned int irq = esp->host->irq;

	scsi_esp_unregister(esp);

	spin_lock(&esp_chips_lock);
	esp_chips[dev->id] = NULL;
	if (esp_chips[!dev->id] == NULL) {
		spin_unlock(&esp_chips_lock);
		free_irq(irq, NULL);
	} else
		spin_unlock(&esp_chips_lock);

	kfree(mep);

	kfree(esp->command_block);

	scsi_host_put(esp->host);

	return 0;
}