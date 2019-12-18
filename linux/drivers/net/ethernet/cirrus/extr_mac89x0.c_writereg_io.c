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
struct net_device {scalar_t__ base_addr; } ;

/* Variables and functions */
 scalar_t__ ADD_PORT ; 
 scalar_t__ DATA_PORT ; 
 int /*<<< orphan*/  nubus_writew (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  swab16 (int) ; 

__attribute__((used)) static inline void
writereg_io(struct net_device *dev, int portno, int value)
{
	nubus_writew(swab16(portno), dev->base_addr + ADD_PORT);
	nubus_writew(swab16(value), dev->base_addr + DATA_PORT);
}