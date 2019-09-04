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

/* Variables and functions */
 int /*<<< orphan*/  bt3c_address (unsigned int,unsigned short) ; 
 int /*<<< orphan*/  bt3c_put (unsigned int,unsigned short) ; 

__attribute__((used)) static inline void bt3c_io_write(unsigned int iobase, unsigned short addr, unsigned short value)
{
	bt3c_address(iobase, addr);
	bt3c_put(iobase, value);
}