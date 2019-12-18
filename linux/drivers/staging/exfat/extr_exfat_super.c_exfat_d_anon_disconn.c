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
struct dentry {int d_flags; } ;

/* Variables and functions */
 int DCACHE_DISCONNECTED ; 
 scalar_t__ IS_ROOT (struct dentry*) ; 

__attribute__((used)) static int exfat_d_anon_disconn(struct dentry *dentry)
{
	return IS_ROOT(dentry) && (dentry->d_flags & DCACHE_DISCONNECTED);
}