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
typedef  scalar_t__ u32 ;
struct cmac {int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  vsc_read (int /*<<< orphan*/ ,unsigned int,scalar_t__*) ; 

__attribute__((used)) static void rmon_update(struct cmac *mac, unsigned int addr, u64 *stat)
{
	u32 v, lo;

	vsc_read(mac->adapter, addr, &v);
	lo = *stat;
	*stat = *stat - lo + v;

	if (v == 0)
		return;

	if (v < lo)
		*stat += (1ULL << 32);
}