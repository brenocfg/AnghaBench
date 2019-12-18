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
struct cmac {int offset; } ;

/* Variables and functions */
 int XGMAC0_0_BASE_ADDR ; 
 int XGMAC0_1_BASE_ADDR ; 

__attribute__((used)) static inline int macidx(const struct cmac *mac)
{
	return mac->offset / (XGMAC0_1_BASE_ADDR - XGMAC0_0_BASE_ADDR);
}