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
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  __module_get (int /*<<< orphan*/ ) ; 
 int epx_c3_alive ; 
 int /*<<< orphan*/  epx_c3_pet () ; 
 int /*<<< orphan*/  epx_c3_start () ; 
 scalar_t__ nowayout ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int stream_open (struct inode*,struct file*) ; 

__attribute__((used)) static int epx_c3_open(struct inode *inode, struct file *file)
{
	if (epx_c3_alive)
		return -EBUSY;

	if (nowayout)
		__module_get(THIS_MODULE);

	/* Activate timer */
	epx_c3_start();
	epx_c3_pet();

	epx_c3_alive = 1;
	pr_info("Started watchdog timer\n");

	return stream_open(inode, file);
}