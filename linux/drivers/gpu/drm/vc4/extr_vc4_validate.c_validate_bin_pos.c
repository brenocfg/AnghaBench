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
typedef  int uint32_t ;
struct vc4_exec_info {void* bin_u; } ;

/* Variables and functions */

__attribute__((used)) static bool
validate_bin_pos(struct vc4_exec_info *exec, void *untrusted, uint32_t pos)
{
	/* Note that the untrusted pointer passed to these functions is
	 * incremented past the packet byte.
	 */
	return (untrusted - 1 == exec->bin_u + pos);
}