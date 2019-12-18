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
struct sl811 {int /*<<< orphan*/  debug_file; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_IRUGO ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sl811*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sl811h_debug_fops ; 
 int /*<<< orphan*/  usb_debug_root ; 

__attribute__((used)) static void create_debug_file(struct sl811 *sl811)
{
	sl811->debug_file = debugfs_create_file("sl811h", S_IRUGO,
						usb_debug_root, sl811,
						&sl811h_debug_fops);
}