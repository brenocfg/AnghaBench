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
struct bcm2835_desc {size_t size; } ;

/* Variables and functions */

__attribute__((used)) static size_t bcm2835_dma_desc_size(struct bcm2835_desc *d)
{
	return d->size;
}