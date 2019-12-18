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
struct dma_info {scalar_t__ d64txregbase; scalar_t__ d64rxregbase; int /*<<< orphan*/  name; int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA64RXREGOFFS (struct dma_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA64TXREGOFFS (struct dma_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _dma64_addrext (struct dma_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_dbg_dma (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  control ; 

__attribute__((used)) static bool _dma_isaddrext(struct dma_info *di)
{
	/* DMA64 supports full 32- or 64-bit operation. AE is always valid */

	/* not all tx or rx channel are available */
	if (di->d64txregbase != 0) {
		if (!_dma64_addrext(di, DMA64TXREGOFFS(di, control)))
			brcms_dbg_dma(di->core,
				      "%s: DMA64 tx doesn't have AE set\n",
				      di->name);
		return true;
	} else if (di->d64rxregbase != 0) {
		if (!_dma64_addrext(di, DMA64RXREGOFFS(di, control)))
			brcms_dbg_dma(di->core,
				      "%s: DMA64 rx doesn't have AE set\n",
				      di->name);
		return true;
	}

	return false;
}