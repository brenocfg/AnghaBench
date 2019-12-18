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
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct goldfish_audio {scalar_t__ irq; int buffer_phys; scalar_t__ read_supported; scalar_t__ buffer_virt; scalar_t__ read_buffer; scalar_t__ write_buffer2; scalar_t__ write_buffer1; int /*<<< orphan*/  reg_base; int /*<<< orphan*/  wait; int /*<<< orphan*/  lock; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_READ_SUPPORTED ; 
 int /*<<< orphan*/  AUDIO_SET_READ_BUFFER ; 
 int /*<<< orphan*/  AUDIO_SET_READ_BUFFER_HIGH ; 
 int /*<<< orphan*/  AUDIO_SET_WRITE_BUFFER_1 ; 
 int /*<<< orphan*/  AUDIO_SET_WRITE_BUFFER_1_HIGH ; 
 int /*<<< orphan*/  AUDIO_SET_WRITE_BUFFER_2 ; 
 int /*<<< orphan*/  AUDIO_SET_WRITE_BUFFER_2_HIGH ; 
 int /*<<< orphan*/  COMBINED_BUFFER_SIZE ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int WRITE_BUFFER_SIZE ; 
 struct goldfish_audio* audio_data ; 
 scalar_t__ audio_read (struct goldfish_audio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audio_write64 (struct goldfish_audio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  devm_ioremap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct goldfish_audio* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct goldfish_audio*) ; 
 scalar_t__ dmam_alloc_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  goldfish_audio_device ; 
 int /*<<< orphan*/  goldfish_audio_interrupt ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int misc_register (int /*<<< orphan*/ *) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct goldfish_audio*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int goldfish_audio_probe(struct platform_device *pdev)
{
	int ret;
	struct resource *r;
	struct goldfish_audio *data;
	dma_addr_t buf_addr;

	data = devm_kzalloc(&pdev->dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;
	spin_lock_init(&data->lock);
	init_waitqueue_head(&data->wait);
	platform_set_drvdata(pdev, data);

	r = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!r) {
		dev_err(&pdev->dev, "platform_get_resource failed\n");
		return -ENODEV;
	}
	data->reg_base = devm_ioremap(&pdev->dev, r->start, PAGE_SIZE);
	if (!data->reg_base)
		return -ENOMEM;

	data->irq = platform_get_irq(pdev, 0);
	if (data->irq < 0)
		return -ENODEV;
	data->buffer_virt = dmam_alloc_coherent(&pdev->dev,
						COMBINED_BUFFER_SIZE,
						&buf_addr, GFP_KERNEL);
	if (!data->buffer_virt) {
		dev_err(&pdev->dev, "allocate buffer failed\n");
		return -ENOMEM;
	}
	data->buffer_phys = buf_addr;
	data->write_buffer1 = data->buffer_virt;
	data->write_buffer2 = data->buffer_virt + WRITE_BUFFER_SIZE;
	data->read_buffer = data->buffer_virt + 2 * WRITE_BUFFER_SIZE;

	ret = devm_request_irq(&pdev->dev, data->irq, goldfish_audio_interrupt,
			       IRQF_SHARED, pdev->name, data);
	if (ret) {
		dev_err(&pdev->dev, "request_irq failed\n");
		return ret;
	}

	ret = misc_register(&goldfish_audio_device);
	if (ret) {
		dev_err(&pdev->dev,
			"misc_register returned %d in goldfish_audio_init\n",
								ret);
		return ret;
	}

	audio_write64(data, AUDIO_SET_WRITE_BUFFER_1,
		      AUDIO_SET_WRITE_BUFFER_1_HIGH, buf_addr);
	buf_addr += WRITE_BUFFER_SIZE;

	audio_write64(data, AUDIO_SET_WRITE_BUFFER_2,
		      AUDIO_SET_WRITE_BUFFER_2_HIGH, buf_addr);

	buf_addr += WRITE_BUFFER_SIZE;

	data->read_supported = audio_read(data, AUDIO_READ_SUPPORTED);
	if (data->read_supported)
		audio_write64(data, AUDIO_SET_READ_BUFFER,
			      AUDIO_SET_READ_BUFFER_HIGH, buf_addr);

	audio_data = data;
	return 0;
}