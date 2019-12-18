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
struct nvkm_fault_buffer {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void
tu102_fault_buffer_intr(struct nvkm_fault_buffer *buffer, bool enable)
{
	/*XXX: Earlier versions of RM touched the old regs on Turing,
	 *     which don't appear to actually work anymore, but newer
	 *     versions of RM don't appear to touch anything at all..
	 */
}