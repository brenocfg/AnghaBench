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
struct isp1362_hcd {int /*<<< orphan*/  debug_file; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_IRUGO ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct isp1362_hcd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isp1362_fops ; 
 int /*<<< orphan*/  usb_debug_root ; 

__attribute__((used)) static void create_debug_file(struct isp1362_hcd *isp1362_hcd)
{
	isp1362_hcd->debug_file = debugfs_create_file("isp1362", S_IRUGO,
						      usb_debug_root,
						      isp1362_hcd,
						      &isp1362_fops);
}