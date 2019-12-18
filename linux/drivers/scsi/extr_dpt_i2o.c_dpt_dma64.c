#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_3__ {scalar_t__ dma64; } ;
typedef  TYPE_1__ adpt_hba ;

/* Variables and functions */

__attribute__((used)) static inline int dpt_dma64(adpt_hba *pHba)
{
	return (sizeof(dma_addr_t) > 4 && (pHba)->dma64);
}