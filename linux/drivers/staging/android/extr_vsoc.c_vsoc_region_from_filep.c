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
struct vsoc_device_region {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  file_inode (struct file*) ; 
 struct vsoc_device_region* vsoc_region_from_inode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
inline struct vsoc_device_region *vsoc_region_from_filep(struct file *inode)
{
	return vsoc_region_from_inode(file_inode(inode));
}