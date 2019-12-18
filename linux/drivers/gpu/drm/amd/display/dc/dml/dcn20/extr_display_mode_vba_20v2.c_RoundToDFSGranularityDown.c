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
 double dml_ceil (double,int) ; 

__attribute__((used)) static double RoundToDFSGranularityDown(double Clock, double VCOSpeed)
{
	return VCOSpeed * 4 / dml_ceil(VCOSpeed * 4 / Clock, 1);
}