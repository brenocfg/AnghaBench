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
struct mic_dma_chan {int dummy; } ;
struct mbus_device {int dummy; } ;
struct TYPE_2__ {struct mbus_device* mbdev; } ;

/* Variables and functions */
 TYPE_1__* to_mic_dma_dev (struct mic_dma_chan*) ; 

__attribute__((used)) static inline struct mbus_device *to_mbus_device(struct mic_dma_chan *ch)
{
	return to_mic_dma_dev(ch)->mbdev;
}