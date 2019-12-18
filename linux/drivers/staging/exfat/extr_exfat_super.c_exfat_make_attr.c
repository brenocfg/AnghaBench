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
typedef  int u32 ;
struct inode {int i_mode; } ;
struct TYPE_3__ {int attr; } ;
struct TYPE_4__ {TYPE_1__ fid; } ;

/* Variables and functions */
 int ATTR_READONLY ; 
 TYPE_2__* EXFAT_I (struct inode*) ; 
 scalar_t__ exfat_mode_can_hold_ro (struct inode*) ; 

__attribute__((used)) static inline u32 exfat_make_attr(struct inode *inode)
{
	if (exfat_mode_can_hold_ro(inode) && !(inode->i_mode & 0222))
		return (EXFAT_I(inode)->fid.attr) | ATTR_READONLY;
	else
		return EXFAT_I(inode)->fid.attr;
}