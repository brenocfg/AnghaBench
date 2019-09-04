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
 scalar_t__ dcn_bw_floor2 (double,double) ; 

__attribute__((used)) static inline double dml_floor_ex(double x, double granularity)
{
	return (double) dcn_bw_floor2(x, granularity);
}