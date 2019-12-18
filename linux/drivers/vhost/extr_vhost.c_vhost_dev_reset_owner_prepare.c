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
struct vhost_umem {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct vhost_umem* kvzalloc (int,int /*<<< orphan*/ ) ; 

struct vhost_umem *vhost_dev_reset_owner_prepare(void)
{
	return kvzalloc(sizeof(struct vhost_umem), GFP_KERNEL);
}