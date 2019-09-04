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
typedef  scalar_t__ u64 ;
struct nitrox_device {scalar_t__ bar_addr; } ;

/* Variables and functions */
 scalar_t__ readq (scalar_t__) ; 

__attribute__((used)) static inline u64 nitrox_read_csr(struct nitrox_device *ndev, u64 offset)
{
	return readq(ndev->bar_addr + offset);
}