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
struct sdma_engine {struct hfi1_devdata* dd; } ;
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_ENABLE ; 
 int /*<<< orphan*/  SD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfi1_pkt_base_sdma_integrity (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  write_sde_csr (struct sdma_engine*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_sdma_integrity(struct sdma_engine *sde)
{
	struct hfi1_devdata *dd = sde->dd;

	write_sde_csr(sde, SD(CHECK_ENABLE),
		      hfi1_pkt_base_sdma_integrity(dd));
}