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
typedef  int /*<<< orphan*/  u64 ;
struct cvm_mmc_host {scalar_t__ base; int /*<<< orphan*/  has_ciu3; } ;

/* Variables and functions */
 scalar_t__ MIO_EMM_INT (struct cvm_mmc_host*) ; 
 scalar_t__ MIO_EMM_INT_EN (struct cvm_mmc_host*) ; 
 int /*<<< orphan*/  writeq (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void octeon_mmc_int_enable(struct cvm_mmc_host *host, u64 val)
{
	writeq(val, host->base + MIO_EMM_INT(host));
	if (!host->has_ciu3)
		writeq(val, host->base + MIO_EMM_INT_EN(host));
}