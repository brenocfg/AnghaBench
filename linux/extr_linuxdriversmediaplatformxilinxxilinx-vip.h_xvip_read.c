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
typedef  scalar_t__ u32 ;
struct xvip_device {scalar_t__ iomem; } ;

/* Variables and functions */
 scalar_t__ ioread32 (scalar_t__) ; 

__attribute__((used)) static inline u32 xvip_read(struct xvip_device *xvip, u32 addr)
{
	return ioread32(xvip->iomem + addr);
}