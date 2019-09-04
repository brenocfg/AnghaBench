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
struct fru_common_header {int dummy; } ;

/* Variables and functions */
 char* __fru_alloc_get_tl (struct fru_common_header*,int) ; 

char *fru_get_serial_number(struct fru_common_header *header)
{
	return __fru_alloc_get_tl(header, 2);
}