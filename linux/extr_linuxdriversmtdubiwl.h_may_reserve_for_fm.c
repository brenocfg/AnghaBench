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
struct ubi_wl_entry {int dummy; } ;
struct ubi_device {int dummy; } ;
struct rb_root {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct ubi_wl_entry *may_reserve_for_fm(struct ubi_device *ubi,
					       struct ubi_wl_entry *e,
					       struct rb_root *root) {
	return e;
}