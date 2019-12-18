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
struct tcs_group {int dummy; } ;
struct rsc_drv {struct tcs_group* tcs; } ;

/* Variables and functions */

__attribute__((used)) static struct tcs_group *get_tcs_of_type(struct rsc_drv *drv, int type)
{
	return &drv->tcs[type];
}