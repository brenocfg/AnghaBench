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

/* Variables and functions */
 int /*<<< orphan*/  GFX_OP_PIPE_CONTROL (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline u32 *gen8_emit_pipe_control(u32 *batch, u32 flags, u32 offset)
{
	memset(batch, 0, 6 * sizeof(u32));

	batch[0] = GFX_OP_PIPE_CONTROL(6);
	batch[1] = flags;
	batch[2] = offset;

	return batch + 6;
}