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
struct seq_file {struct adf_cfg_device_data* private; } ;
struct adf_cfg_device_data {int /*<<< orphan*/  sec_list; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 void* seq_list_next (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *qat_dev_cfg_next(struct seq_file *sfile, void *v, loff_t *pos)
{
	struct adf_cfg_device_data *dev_cfg = sfile->private;

	return seq_list_next(v, &dev_cfg->sec_list, pos);
}