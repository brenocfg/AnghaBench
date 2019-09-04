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
struct diag204_x_part_hdr {int dummy; } ;
struct diag204_part_hdr {int dummy; } ;
typedef  enum diag204_format { ____Placeholder_diag204_format } diag204_format ;

/* Variables and functions */
 int DIAG204_INFO_SIMPLE ; 

__attribute__((used)) static inline int part_hdr__size(enum diag204_format type)
{
	if (type == DIAG204_INFO_SIMPLE)
		return sizeof(struct diag204_part_hdr);
	else /* DIAG204_INFO_EXT */
		return sizeof(struct diag204_x_part_hdr);
}