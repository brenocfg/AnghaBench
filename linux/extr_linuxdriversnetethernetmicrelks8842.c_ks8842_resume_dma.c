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
struct ks8842_adapter {scalar_t__ hw_addr; } ;

/* Variables and functions */
 scalar_t__ REQ_TIMB_DMA_RESUME ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 

__attribute__((used)) static inline void ks8842_resume_dma(struct ks8842_adapter *adapter)
{
	iowrite32(1, adapter->hw_addr + REQ_TIMB_DMA_RESUME);
}