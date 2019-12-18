#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct Scsi_Host {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  mode; } ;
typedef  TYPE_1__ imm_struct ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_1__* imm_dev (struct Scsi_Host*) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  simple_strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static int imm_write_info(struct Scsi_Host *host, char *buffer, int length)
{
	imm_struct *dev = imm_dev(host);

	if ((length > 5) && (strncmp(buffer, "mode=", 5) == 0)) {
		dev->mode = simple_strtoul(buffer + 5, NULL, 0);
		return length;
	}
	printk("imm /proc: invalid variable\n");
	return -EINVAL;
}