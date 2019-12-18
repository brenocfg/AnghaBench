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
struct gpmc_cs_data {char const* name; } ;

/* Variables and functions */
 struct gpmc_cs_data* gpmc_cs ; 

__attribute__((used)) static void gpmc_cs_set_name(int cs, const char *name)
{
	struct gpmc_cs_data *gpmc = &gpmc_cs[cs];

	gpmc->name = name;
}