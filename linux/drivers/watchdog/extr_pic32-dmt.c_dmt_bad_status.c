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
typedef  int u32 ;
struct pic32_dmt {scalar_t__ regs; } ;

/* Variables and functions */
 int DMTSTAT_BAD1 ; 
 int DMTSTAT_BAD2 ; 
 int DMTSTAT_EVENT ; 
 scalar_t__ DMTSTAT_REG ; 
 int EAGAIN ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static inline int dmt_bad_status(struct pic32_dmt *dmt)
{
	u32 val;

	val = readl(dmt->regs + DMTSTAT_REG);
	val &= (DMTSTAT_BAD1 | DMTSTAT_BAD2 | DMTSTAT_EVENT);
	if (val)
		return -EAGAIN;

	return 0;
}