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
typedef  int u64 ;
struct be_dma_mem {int size; int /*<<< orphan*/  dma; int /*<<< orphan*/  va; } ;
struct be_cmd_req_ddrdma_test {int dummy; } ;
struct be_adapter {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int be_cmd_ddr_dma_test (struct be_adapter*,int const,int,struct be_dma_mem*) ; 
 int be_cmd_status (int) ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int be_test_ddr_dma(struct be_adapter *adapter)
{
	int ret, i;
	struct be_dma_mem ddrdma_cmd;
	static const u64 pattern[2] = {
		0x5a5a5a5a5a5a5a5aULL, 0xa5a5a5a5a5a5a5a5ULL
	};

	ddrdma_cmd.size = sizeof(struct be_cmd_req_ddrdma_test);
	ddrdma_cmd.va = dma_alloc_coherent(&adapter->pdev->dev,
					   ddrdma_cmd.size, &ddrdma_cmd.dma,
					   GFP_KERNEL);
	if (!ddrdma_cmd.va)
		return -ENOMEM;

	for (i = 0; i < 2; i++) {
		ret = be_cmd_ddr_dma_test(adapter, pattern[i],
					  4096, &ddrdma_cmd);
		if (ret != 0)
			goto err;
	}

err:
	dma_free_coherent(&adapter->pdev->dev, ddrdma_cmd.size, ddrdma_cmd.va,
			  ddrdma_cmd.dma);
	return be_cmd_status(ret);
}