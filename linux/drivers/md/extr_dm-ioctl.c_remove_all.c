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
struct file {int dummy; } ;
struct dm_ioctl {int flags; scalar_t__ data_size; } ;

/* Variables and functions */
 int DM_DEFERRED_REMOVE ; 
 int /*<<< orphan*/  dm_hash_remove_all (int,int,int) ; 

__attribute__((used)) static int remove_all(struct file *filp, struct dm_ioctl *param, size_t param_size)
{
	dm_hash_remove_all(true, !!(param->flags & DM_DEFERRED_REMOVE), false);
	param->data_size = 0;
	return 0;
}