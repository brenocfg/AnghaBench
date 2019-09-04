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
struct proxy_dev {int /*<<< orphan*/  state; } ;
struct file {struct proxy_dev* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  STATE_OPENED_FLAG ; 

__attribute__((used)) static void vtpm_proxy_fops_open(struct file *filp)
{
	struct proxy_dev *proxy_dev = filp->private_data;

	proxy_dev->state |= STATE_OPENED_FLAG;
}