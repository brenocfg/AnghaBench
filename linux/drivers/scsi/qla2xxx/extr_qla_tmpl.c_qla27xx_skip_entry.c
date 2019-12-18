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
struct TYPE_2__ {int /*<<< orphan*/  driver_flags; } ;
struct qla27xx_fwdt_entry {TYPE_1__ hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_FLAG_SKIP_ENTRY ; 

__attribute__((used)) static inline void
qla27xx_skip_entry(struct qla27xx_fwdt_entry *ent, void *buf)
{
	if (buf)
		ent->hdr.driver_flags |= DRIVER_FLAG_SKIP_ENTRY;
}