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
typedef  int u64 ;
struct device {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int PHYS_OFFSET ; 
 int SZ_64M ; 

int dma_set_coherent_mask(struct device *dev, u64 mask)
{
	if (mask >= PHYS_OFFSET + SZ_64M - 1)
		return 0;

	return -EIO;
}