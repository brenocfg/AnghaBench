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
struct spi_device {int bits_per_word; int mode; int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;
struct pcap_platform_data {int config; int irq_base; int num_subdevs; int /*<<< orphan*/  (* init ) (struct pcap_chip*) ;int /*<<< orphan*/ * subdevs; } ;
struct pcap_chip {int irq_base; int msr; int /*<<< orphan*/  workqueue; struct spi_device* spi; int /*<<< orphan*/  msr_work; int /*<<< orphan*/  isr_work; int /*<<< orphan*/  adc_lock; int /*<<< orphan*/  io_lock; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IRQ_NOPROBE ; 
 int IRQ_NOREQUEST ; 
 int /*<<< orphan*/  IRQ_TYPE_EDGE_RISING ; 
 int PCAP_CLEAR_INTERRUPT_REGISTER ; 
 int PCAP_CS_AH ; 
 int PCAP_IRQ_ADCDONE ; 
 int PCAP_IRQ_ADCDONE2 ; 
 int PCAP_MASK_ALL_INTERRUPT ; 
 int PCAP_NIRQS ; 
 int /*<<< orphan*/  PCAP_REG_INT_SEL ; 
 int /*<<< orphan*/  PCAP_REG_ISR ; 
 int /*<<< orphan*/  PCAP_REG_MSR ; 
 int PCAP_SECOND_PORT ; 
 int SPI_CS_HIGH ; 
 int SPI_MODE_0 ; 
 int /*<<< orphan*/  create_singlethread_workqueue (char*) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct pcap_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_for_each_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct pcap_chip* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct pcap_chip*) ; 
 int /*<<< orphan*/  ezx_pcap_write (struct pcap_chip*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * handle_simple_irq ; 
 int /*<<< orphan*/  irq_clear_status_flags (int,int) ; 
 int /*<<< orphan*/  irq_set_chained_handler_and_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pcap_chip*) ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_set_chip_data (int,struct pcap_chip*) ; 
 int /*<<< orphan*/  irq_set_irq_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_irq_wake (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pcap_adc_irq ; 
 int pcap_add_subdev (struct pcap_chip*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcap_irq_chip ; 
 int /*<<< orphan*/  pcap_irq_handler ; 
 int /*<<< orphan*/  pcap_isr_work ; 
 int /*<<< orphan*/  pcap_msr_work ; 
 int /*<<< orphan*/  pcap_remove_subdev ; 
 int pcap_to_irq (struct pcap_chip*,int) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct pcap_chip*) ; 
 int spi_setup (struct spi_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct pcap_chip*) ; 

__attribute__((used)) static int ezx_pcap_probe(struct spi_device *spi)
{
	struct pcap_platform_data *pdata = dev_get_platdata(&spi->dev);
	struct pcap_chip *pcap;
	int i, adc_irq;
	int ret = -ENODEV;

	/* platform data is required */
	if (!pdata)
		goto ret;

	pcap = devm_kzalloc(&spi->dev, sizeof(*pcap), GFP_KERNEL);
	if (!pcap) {
		ret = -ENOMEM;
		goto ret;
	}

	spin_lock_init(&pcap->io_lock);
	spin_lock_init(&pcap->adc_lock);
	INIT_WORK(&pcap->isr_work, pcap_isr_work);
	INIT_WORK(&pcap->msr_work, pcap_msr_work);
	spi_set_drvdata(spi, pcap);

	/* setup spi */
	spi->bits_per_word = 32;
	spi->mode = SPI_MODE_0 | (pdata->config & PCAP_CS_AH ? SPI_CS_HIGH : 0);
	ret = spi_setup(spi);
	if (ret)
		goto ret;

	pcap->spi = spi;

	/* setup irq */
	pcap->irq_base = pdata->irq_base;
	pcap->workqueue = create_singlethread_workqueue("pcapd");
	if (!pcap->workqueue) {
		ret = -ENOMEM;
		dev_err(&spi->dev, "can't create pcap thread\n");
		goto ret;
	}

	/* redirect interrupts to AP, except adcdone2 */
	if (!(pdata->config & PCAP_SECOND_PORT))
		ezx_pcap_write(pcap, PCAP_REG_INT_SEL,
					(1 << PCAP_IRQ_ADCDONE2));

	/* setup irq chip */
	for (i = pcap->irq_base; i < (pcap->irq_base + PCAP_NIRQS); i++) {
		irq_set_chip_and_handler(i, &pcap_irq_chip, handle_simple_irq);
		irq_set_chip_data(i, pcap);
		irq_clear_status_flags(i, IRQ_NOREQUEST | IRQ_NOPROBE);
	}

	/* mask/ack all PCAP interrupts */
	ezx_pcap_write(pcap, PCAP_REG_MSR, PCAP_MASK_ALL_INTERRUPT);
	ezx_pcap_write(pcap, PCAP_REG_ISR, PCAP_CLEAR_INTERRUPT_REGISTER);
	pcap->msr = PCAP_MASK_ALL_INTERRUPT;

	irq_set_irq_type(spi->irq, IRQ_TYPE_EDGE_RISING);
	irq_set_chained_handler_and_data(spi->irq, pcap_irq_handler, pcap);
	irq_set_irq_wake(spi->irq, 1);

	/* ADC */
	adc_irq = pcap_to_irq(pcap, (pdata->config & PCAP_SECOND_PORT) ?
					PCAP_IRQ_ADCDONE2 : PCAP_IRQ_ADCDONE);

	ret = devm_request_irq(&spi->dev, adc_irq, pcap_adc_irq, 0, "ADC",
				pcap);
	if (ret)
		goto free_irqchip;

	/* setup subdevs */
	for (i = 0; i < pdata->num_subdevs; i++) {
		ret = pcap_add_subdev(pcap, &pdata->subdevs[i]);
		if (ret)
			goto remove_subdevs;
	}

	/* board specific quirks */
	if (pdata->init)
		pdata->init(pcap);

	return 0;

remove_subdevs:
	device_for_each_child(&spi->dev, NULL, pcap_remove_subdev);
free_irqchip:
	for (i = pcap->irq_base; i < (pcap->irq_base + PCAP_NIRQS); i++)
		irq_set_chip_and_handler(i, NULL, NULL);
/* destroy_workqueue: */
	destroy_workqueue(pcap->workqueue);
ret:
	return ret;
}