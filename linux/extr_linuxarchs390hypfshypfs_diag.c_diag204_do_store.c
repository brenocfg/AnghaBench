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
 int ENOSYS ; 
 int diag204 (unsigned long,int,void*) ; 
 scalar_t__ diag204_info_type ; 
 scalar_t__ diag204_store_sc ; 

__attribute__((used)) static int diag204_do_store(void *buf, int pages)
{
	int rc;

	rc = diag204((unsigned long) diag204_store_sc |
		     (unsigned long) diag204_info_type, pages, buf);
	return rc < 0 ? -ENOSYS : 0;
}