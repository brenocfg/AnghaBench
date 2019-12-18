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
struct cami2c {scalar_t__ iobase; } ;

/* Variables and functions */
 int /*<<< orphan*/  __raw_writel (unsigned long,unsigned long) ; 

__attribute__((used)) static inline void OUT32(struct cami2c *cam, int reg, unsigned long val)
{
	__raw_writel(val, (unsigned long)cam->iobase + reg);
}