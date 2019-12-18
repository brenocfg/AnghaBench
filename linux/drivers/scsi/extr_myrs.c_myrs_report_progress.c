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
struct myrs_hba {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  shost_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned short,unsigned char*,int) ; 

__attribute__((used)) static void myrs_report_progress(struct myrs_hba *cs, unsigned short ldev_num,
		unsigned char *msg, unsigned long blocks,
		unsigned long size)
{
	shost_printk(KERN_INFO, cs->host,
		     "Logical Drive %d: %s in Progress: %d%% completed\n",
		     ldev_num, msg,
		     (100 * (int)(blocks >> 7)) / (int)(size >> 7));
}