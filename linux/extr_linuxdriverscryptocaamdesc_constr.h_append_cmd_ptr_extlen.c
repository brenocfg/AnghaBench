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
typedef  unsigned int u32 ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 unsigned int SQIN_PRE ; 
 unsigned int SQIN_RTO ; 
 int /*<<< orphan*/  append_cmd (unsigned int* const,unsigned int) ; 
 int /*<<< orphan*/  append_ptr (unsigned int* const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void append_cmd_ptr_extlen(u32 * const desc, dma_addr_t ptr,
					 unsigned int len, u32 command)
{
	append_cmd(desc, command);
	if (!(command & (SQIN_RTO | SQIN_PRE)))
		append_ptr(desc, ptr);
	append_cmd(desc, len);
}