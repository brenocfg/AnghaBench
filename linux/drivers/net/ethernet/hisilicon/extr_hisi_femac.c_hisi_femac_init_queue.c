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
struct sk_buff {int dummy; } ;
struct hisi_femac_queue {unsigned int num; scalar_t__ tail; scalar_t__ head; void* dma_phys; void* skb; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* devm_kcalloc (struct device*,unsigned int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hisi_femac_init_queue(struct device *dev,
				 struct hisi_femac_queue *queue,
				 unsigned int num)
{
	queue->skb = devm_kcalloc(dev, num, sizeof(struct sk_buff *),
				  GFP_KERNEL);
	if (!queue->skb)
		return -ENOMEM;

	queue->dma_phys = devm_kcalloc(dev, num, sizeof(dma_addr_t),
				       GFP_KERNEL);
	if (!queue->dma_phys)
		return -ENOMEM;

	queue->num = num;
	queue->head = 0;
	queue->tail = 0;

	return 0;
}