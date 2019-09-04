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
typedef  scalar_t__ u64 ;

/* Variables and functions */
 scalar_t__ _4GB ; 
 scalar_t__ top_lm ; 

__attribute__((used)) static u64 remove_mmio_gap(u64 sys)
{
	return (sys < _4GB) ? sys : sys - (_4GB - top_lm);
}