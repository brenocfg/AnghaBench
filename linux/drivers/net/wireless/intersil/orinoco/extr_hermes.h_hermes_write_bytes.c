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
struct hermes {int reg_spacing; scalar_t__ iobase; } ;

/* Variables and functions */
 int /*<<< orphan*/  iowrite16_rep (scalar_t__,char const*,unsigned int) ; 
 int /*<<< orphan*/  iowrite8 (char const,scalar_t__) ; 
 scalar_t__ unlikely (unsigned int) ; 

__attribute__((used)) static inline void hermes_write_bytes(struct hermes *hw, int off,
				      const char *buf, unsigned count)
{
	off = off << hw->reg_spacing;
	iowrite16_rep(hw->iobase + off, buf, count >> 1);
	if (unlikely(count & 1))
		iowrite8(buf[count - 1], hw->iobase + off);
}