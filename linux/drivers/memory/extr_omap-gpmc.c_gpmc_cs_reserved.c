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
struct gpmc_cs_data {int flags; } ;

/* Variables and functions */
 int GPMC_CS_RESERVED ; 
 struct gpmc_cs_data* gpmc_cs ; 

__attribute__((used)) static bool gpmc_cs_reserved(int cs)
{
	struct gpmc_cs_data *gpmc = &gpmc_cs[cs];

	return gpmc->flags & GPMC_CS_RESERVED;
}