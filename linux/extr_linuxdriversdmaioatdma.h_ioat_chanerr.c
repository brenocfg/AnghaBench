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
typedef  int /*<<< orphan*/  u32 ;
struct ioatdma_chan {scalar_t__ reg_base; } ;

/* Variables and functions */
 scalar_t__ IOAT_CHANERR_OFFSET ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 

__attribute__((used)) static inline u32 ioat_chanerr(struct ioatdma_chan *ioat_chan)
{
	return readl(ioat_chan->reg_base + IOAT_CHANERR_OFFSET);
}