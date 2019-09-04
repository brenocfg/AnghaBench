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
struct cudbg_init {scalar_t__ compress_buff; } ;

/* Variables and functions */
 int /*<<< orphan*/  vfree (scalar_t__) ; 

__attribute__((used)) static void cudbg_free_compress_buff(struct cudbg_init *pdbg_init)
{
	if (pdbg_init->compress_buff)
		vfree(pdbg_init->compress_buff);
}