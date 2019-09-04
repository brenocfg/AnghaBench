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

/* Variables and functions */
 int /*<<< orphan*/  SYSCFGID ; 
 unsigned int get_er (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int get_core_id(void)
{
	/* Bits 0...18 of SYSCFGID contain the core id  */
	unsigned int core_id = get_er(SYSCFGID);
	return core_id & 0x3fff;
}