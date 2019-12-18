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
struct spi_device {int /*<<< orphan*/  dev; } ;
struct pcap_chip {int irq_base; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  adc_lock; int /*<<< orphan*/ * adc_queue; } ;

/* Variables and functions */
 int PCAP_ADC_MAXQ ; 
 int PCAP_NIRQS ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_for_each_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcap_remove_subdev ; 
 struct pcap_chip* spi_get_drvdata (struct spi_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ezx_pcap_remove(struct spi_device *spi)
{
	struct pcap_chip *pcap = spi_get_drvdata(spi);
	unsigned long flags;
	int i;

	/* remove all registered subdevs */
	device_for_each_child(&spi->dev, NULL, pcap_remove_subdev);

	/* cleanup ADC */
	spin_lock_irqsave(&pcap->adc_lock, flags);
	for (i = 0; i < PCAP_ADC_MAXQ; i++)
		kfree(pcap->adc_queue[i]);
	spin_unlock_irqrestore(&pcap->adc_lock, flags);

	/* cleanup irqchip */
	for (i = pcap->irq_base; i < (pcap->irq_base + PCAP_NIRQS); i++)
		irq_set_chip_and_handler(i, NULL, NULL);

	destroy_workqueue(pcap->workqueue);

	return 0;
}