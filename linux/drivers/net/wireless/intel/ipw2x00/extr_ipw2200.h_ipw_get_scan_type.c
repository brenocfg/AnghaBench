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
typedef  int u8 ;
struct ipw_scan_request_ext {int* scan_type; } ;

/* Variables and functions */

__attribute__((used)) static inline u8 ipw_get_scan_type(struct ipw_scan_request_ext *scan, u8 index)
{
	if (index % 2)
		return scan->scan_type[index / 2] & 0x0F;
	else
		return (scan->scan_type[index / 2] & 0xF0) >> 4;
}