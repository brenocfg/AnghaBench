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
typedef  int /*<<< orphan*/  virt_addr_t ;
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  size_t u_int32_t ;
typedef  size_t u_int ;

/* Variables and functions */
 int /*<<< orphan*/  CYCLE_DELAY ; 
 int /*<<< orphan*/  osp_MicroDelay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_eprom_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nicstar_read_eprom(virt_addr_t base,
		   u_int8_t prom_offset, u_int8_t * buffer, u_int32_t nbytes)
{
	u_int i;

	for (i = 0; i < nbytes; i++) {
		buffer[i] = read_eprom_byte(base, prom_offset);
		++prom_offset;
		osp_MicroDelay(CYCLE_DELAY);
	}
}