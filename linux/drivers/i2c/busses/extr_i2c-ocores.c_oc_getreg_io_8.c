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
typedef  int /*<<< orphan*/  u8 ;
struct ocores_i2c {scalar_t__ iobase; } ;

/* Variables and functions */
 int /*<<< orphan*/  inb (scalar_t__) ; 

__attribute__((used)) static inline u8 oc_getreg_io_8(struct ocores_i2c *i2c, int reg)
{
	return inb(i2c->iobase + reg);
}