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
struct cudbg_init {scalar_t__ compress_type; int /*<<< orphan*/  compress_buff_size; int /*<<< orphan*/  compress_buff; } ;
struct cudbg_buffer {scalar_t__ size; scalar_t__ offset; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 scalar_t__ CUDBG_COMPRESSION_NONE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void cudbg_put_buff(struct cudbg_init *pdbg_init,
		    struct cudbg_buffer *pin_buff)
{
	/* Clear compression buffer for re-use */
	if (pdbg_init->compress_type != CUDBG_COMPRESSION_NONE)
		memset(pdbg_init->compress_buff, 0,
		       pdbg_init->compress_buff_size);

	pin_buff->data = NULL;
	pin_buff->offset = 0;
	pin_buff->size = 0;
}