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
 int EINVAL ; 
 int flexrm_spu_dma_map (struct device*,struct brcm_message*) ; 

__attribute__((used)) static int flexrm_dma_map(struct device *dev, struct brcm_message *msg)
{
	if (!dev || !msg)
		return -EINVAL;

	switch (msg->type) {
	case BRCM_MESSAGE_SPU:
		return flexrm_spu_dma_map(dev, msg);
	default:
		break;
	}

	return 0;
}