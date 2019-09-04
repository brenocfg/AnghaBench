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
struct lanai_dev {int /*<<< orphan*/  vccs; } ;

/* Variables and functions */
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void vcc_table_deallocate(const struct lanai_dev *lanai)
{
#ifdef VCCTABLE_GETFREEPAGE
	free_page((unsigned long) lanai->vccs);
#else
	vfree(lanai->vccs);
#endif
}