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
struct ubi_device {int ro_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  dump_stack () ; 
 int /*<<< orphan*/  ubi_warn (struct ubi_device*,char*) ; 

__attribute__((used)) static inline void ubi_ro_mode(struct ubi_device *ubi)
{
	if (!ubi->ro_mode) {
		ubi->ro_mode = 1;
		ubi_warn(ubi, "switch to read-only mode");
		dump_stack();
	}
}