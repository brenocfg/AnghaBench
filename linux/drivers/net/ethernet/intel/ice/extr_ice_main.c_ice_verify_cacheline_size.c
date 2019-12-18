#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ice_pf {TYPE_1__* pdev; int /*<<< orphan*/  hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLPCI_CNF2 ; 
 int GLPCI_CNF2_CACHELINE_SIZE_M ; 
 int /*<<< orphan*/  ICE_CACHE_LINE_BYTES ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int rd32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ice_verify_cacheline_size(struct ice_pf *pf)
{
	if (rd32(&pf->hw, GLPCI_CNF2) & GLPCI_CNF2_CACHELINE_SIZE_M)
		dev_warn(&pf->pdev->dev,
			 "%d Byte cache line assumption is invalid, driver may have Tx timeouts!\n",
			 ICE_CACHE_LINE_BYTES);
}