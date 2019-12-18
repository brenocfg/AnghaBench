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
struct dm_ioctl {int flags; } ;
typedef  int fmode_t ;

/* Variables and functions */
 int DM_READONLY_FLAG ; 
 int FMODE_READ ; 
 int FMODE_WRITE ; 

__attribute__((used)) static inline fmode_t get_mode(struct dm_ioctl *param)
{
	fmode_t mode = FMODE_READ | FMODE_WRITE;

	if (param->flags & DM_READONLY_FLAG)
		mode = FMODE_READ;

	return mode;
}