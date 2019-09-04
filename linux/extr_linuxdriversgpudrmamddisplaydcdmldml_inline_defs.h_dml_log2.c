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
 scalar_t__ dcn_bw_log (double,int) ; 
 int dml_round (double) ; 

__attribute__((used)) static inline int dml_log2(double x)
{
	return dml_round((double)dcn_bw_log(x, 2));
}