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
struct brcm_message {int type; } ;

/* Variables and functions */
#define  BRCM_MESSAGE_SPU 128 
 int /*<<< orphan*/  flexrm_spu_dma_unmap (struct device*,struct brcm_message*) ; 

__attribute__((used)) static void flexrm_dma_unmap(struct device *dev, struct brcm_message *msg)
{
	if (!dev || !msg)
		return;

	switch (msg->type) {
	case BRCM_MESSAGE_SPU:
		flexrm_spu_dma_unmap(dev, msg);
		break;
	default:
		break;
	}
}