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
struct openpic {int dummy; } ;
typedef  int gpa_t ;

/* Variables and functions */
 int openpic_cpu_read_internal (struct openpic*,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int openpic_cpu_read(void *opaque, gpa_t addr, u32 *ptr)
{
	struct openpic *opp = opaque;

	return openpic_cpu_read_internal(opp, addr, ptr,
					 (addr & 0x1f000) >> 12);
}