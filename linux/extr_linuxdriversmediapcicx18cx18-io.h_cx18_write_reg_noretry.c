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
struct cx18 {scalar_t__ reg_mem; } ;

/* Variables and functions */
 int /*<<< orphan*/  cx18_writel_noretry (struct cx18*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline void cx18_write_reg_noretry(struct cx18 *cx, u32 val, u32 reg)
{
	cx18_writel_noretry(cx, val, cx->reg_mem + reg);
}