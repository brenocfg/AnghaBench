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
struct ubi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_bit (int,unsigned long*) ; 
 int /*<<< orphan*/  ubi_dbg_chk_fastmap (struct ubi_device*) ; 

__attribute__((used)) static inline void set_seen(struct ubi_device *ubi, int pnum, unsigned long *seen)
{
	if (!ubi_dbg_chk_fastmap(ubi) || !seen)
		return;

	set_bit(pnum, seen);
}