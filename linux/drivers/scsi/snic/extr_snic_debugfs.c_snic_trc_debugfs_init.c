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
struct TYPE_3__ {int /*<<< orphan*/  trc_file; int /*<<< orphan*/  enable; int /*<<< orphan*/  trc_enable; } ;
struct TYPE_4__ {int /*<<< orphan*/  trc_root; TYPE_1__ trc; } ;

/* Variables and functions */
 int S_IFREG ; 
 int S_IRUGO ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  debugfs_create_bool (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* snic_glob ; 
 int /*<<< orphan*/  snic_trc_fops ; 

void snic_trc_debugfs_init(void)
{
	snic_glob->trc.trc_enable = debugfs_create_bool("tracing_enable",
							S_IFREG | S_IRUGO | S_IWUSR,
							snic_glob->trc_root,
							&snic_glob->trc.enable);

	snic_glob->trc.trc_file = debugfs_create_file("trace",
						      S_IFREG | S_IRUGO | S_IWUSR,
						      snic_glob->trc_root, NULL,
						      &snic_trc_fops);
}