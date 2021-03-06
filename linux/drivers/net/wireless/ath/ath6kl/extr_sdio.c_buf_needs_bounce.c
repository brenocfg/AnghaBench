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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  virt_addr_valid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool buf_needs_bounce(u8 *buf)
{
	return ((unsigned long) buf & 0x3) || !virt_addr_valid(buf);
}