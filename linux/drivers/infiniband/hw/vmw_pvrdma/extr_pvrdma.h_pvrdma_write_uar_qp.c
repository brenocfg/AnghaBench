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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {scalar_t__ map; } ;
struct pvrdma_dev {TYPE_1__ driver_uar; } ;

/* Variables and functions */
 scalar_t__ PVRDMA_UAR_QP_OFFSET ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void pvrdma_write_uar_qp(struct pvrdma_dev *dev, u32 val)
{
	writel(cpu_to_le32(val), dev->driver_uar.map + PVRDMA_UAR_QP_OFFSET);
}