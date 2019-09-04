#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int disable_bgt; } ;
struct ubi_device {TYPE_1__ dbg; } ;

/* Variables and functions */

__attribute__((used)) static inline int ubi_dbg_is_bgt_disabled(const struct ubi_device *ubi)
{
	return ubi->dbg.disable_bgt;
}