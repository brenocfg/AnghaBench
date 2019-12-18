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
typedef  int /*<<< orphan*/  u32 ;
struct ethoc {scalar_t__ iobase; scalar_t__ big_endian; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  ioread32be (scalar_t__) ; 

__attribute__((used)) static inline u32 ethoc_read(struct ethoc *dev, loff_t offset)
{
	if (dev->big_endian)
		return ioread32be(dev->iobase + offset);
	else
		return ioread32(dev->iobase + offset);
}