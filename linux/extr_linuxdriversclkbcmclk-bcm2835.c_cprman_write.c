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
struct bcm2835_cprman {int regs; } ;

/* Variables and functions */
 int CM_PASSWORD ; 
 int /*<<< orphan*/  writel (int,int) ; 

__attribute__((used)) static inline void cprman_write(struct bcm2835_cprman *cprman, u32 reg, u32 val)
{
	writel(CM_PASSWORD | val, cprman->regs + reg);
}