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
typedef  int u32 ;
struct tmc_drvdata {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ TMC_AUTHSTATUS ; 
 int TMC_AUTH_NSID_MASK ; 
 int readl_relaxed (scalar_t__) ; 

__attribute__((used)) static inline bool tmc_etr_has_non_secure_access(struct tmc_drvdata *drvdata)
{
	u32 auth = readl_relaxed(drvdata->base + TMC_AUTHSTATUS);

	return (auth & TMC_AUTH_NSID_MASK) == 0x3;
}