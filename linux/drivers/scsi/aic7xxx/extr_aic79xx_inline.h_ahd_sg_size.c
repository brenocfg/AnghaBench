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
struct ahd_softc {int flags; } ;
struct ahd_dma_seg {int dummy; } ;
struct ahd_dma64_seg {int dummy; } ;

/* Variables and functions */
 int AHD_64BIT_ADDRESSING ; 

__attribute__((used)) static inline size_t ahd_sg_size(struct ahd_softc *ahd)
{
	if ((ahd->flags & AHD_64BIT_ADDRESSING) != 0)
		return (sizeof(struct ahd_dma64_seg));
	return (sizeof(struct ahd_dma_seg));
}