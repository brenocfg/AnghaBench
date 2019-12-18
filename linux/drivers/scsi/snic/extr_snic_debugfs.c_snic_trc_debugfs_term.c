#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * trc_enable; int /*<<< orphan*/ * trc_file; } ;
struct TYPE_4__ {TYPE_1__ trc; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ *) ; 
 TYPE_2__* snic_glob ; 

void
snic_trc_debugfs_term(void)
{
	debugfs_remove(snic_glob->trc.trc_file);
	snic_glob->trc.trc_file = NULL;

	debugfs_remove(snic_glob->trc.trc_enable);
	snic_glob->trc.trc_enable = NULL;
}