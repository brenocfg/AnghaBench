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
struct ctlr_info {scalar_t__ vaddr; } ;

/* Variables and functions */
 int SA5B_INTR_PENDING ; 
 scalar_t__ SA5_INTR_STATUS ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static bool SA5B_intr_pending(struct ctlr_info *h)
{
	return readl(h->vaddr + SA5_INTR_STATUS) & SA5B_INTR_PENDING;
}