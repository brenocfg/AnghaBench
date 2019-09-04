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
struct stm32_hash_dev {scalar_t__ io_base; } ;

/* Variables and functions */
 scalar_t__ readl_relaxed (scalar_t__) ; 

__attribute__((used)) static inline u32 stm32_hash_read(struct stm32_hash_dev *hdev, u32 offset)
{
	return readl_relaxed(hdev->io_base + offset);
}