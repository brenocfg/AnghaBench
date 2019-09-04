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
struct md_cluster_info {int dummy; } ;
struct cluster_msg {int dummy; } ;

/* Variables and functions */
 int __sendmsg (struct md_cluster_info*,struct cluster_msg*) ; 
 int /*<<< orphan*/  lock_comm (struct md_cluster_info*,int) ; 
 int /*<<< orphan*/  unlock_comm (struct md_cluster_info*) ; 

__attribute__((used)) static int sendmsg(struct md_cluster_info *cinfo, struct cluster_msg *cmsg,
		   bool mddev_locked)
{
	int ret;

	lock_comm(cinfo, mddev_locked);
	ret = __sendmsg(cinfo, cmsg);
	unlock_comm(cinfo);
	return ret;
}