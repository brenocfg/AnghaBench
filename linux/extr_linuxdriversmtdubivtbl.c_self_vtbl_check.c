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
struct ubi_device {int /*<<< orphan*/  vtbl; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  ubi_dbg_chk_gen (struct ubi_device const*) ; 
 int /*<<< orphan*/  ubi_err (struct ubi_device const*,char*) ; 
 scalar_t__ vtbl_check (struct ubi_device const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void self_vtbl_check(const struct ubi_device *ubi)
{
	if (!ubi_dbg_chk_gen(ubi))
		return;

	if (vtbl_check(ubi, ubi->vtbl)) {
		ubi_err(ubi, "self-check failed");
		BUG();
	}
}