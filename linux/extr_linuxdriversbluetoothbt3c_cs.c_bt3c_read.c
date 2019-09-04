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
 unsigned short bt3c_get (unsigned int) ; 

__attribute__((used)) static inline unsigned short bt3c_read(unsigned int iobase, unsigned short addr)
{
	bt3c_address(iobase, addr);

	return bt3c_get(iobase);
}