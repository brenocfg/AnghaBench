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
typedef  scalar_t__ u64 ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  phys_to_virt (int /*<<< orphan*/ ) ; 

ssize_t elfcorehdr_read(char *buf, size_t count, u64 *ppos)
{
	memcpy(buf, phys_to_virt((phys_addr_t)*ppos), count);
	return count;
}