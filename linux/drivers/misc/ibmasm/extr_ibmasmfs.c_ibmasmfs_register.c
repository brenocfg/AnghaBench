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

/* Variables and functions */
 int /*<<< orphan*/  ibmasmfs_type ; 
 int register_filesystem (int /*<<< orphan*/ *) ; 

int ibmasmfs_register(void)
{
	return register_filesystem(&ibmasmfs_type);
}