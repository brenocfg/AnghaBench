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
struct TYPE_2__ {int bufsize; } ;
struct saa7134_dev {TYPE_1__ dmasound; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int saa7134_alsa_dma_init (struct saa7134_dev*,int) ; 

__attribute__((used)) static int dsp_buffer_init(struct saa7134_dev *dev)
{
	int err;

	BUG_ON(!dev->dmasound.bufsize);

	err = saa7134_alsa_dma_init(dev,
			       (dev->dmasound.bufsize + PAGE_SIZE) >> PAGE_SHIFT);
	if (0 != err)
		return err;
	return 0;
}