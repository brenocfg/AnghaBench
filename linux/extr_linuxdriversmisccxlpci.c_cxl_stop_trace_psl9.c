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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct cxl {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CXL_PSL9_CTCCFG ; 
 int /*<<< orphan*/  CXL_PSL9_TRACECFG ; 
 int CXL_PSL9_TRACEID_MAX ; 
 int CXL_PSL9_TRACESTATE_FIN ; 
 int cxl_p1_read (struct cxl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxl_p1_write (struct cxl*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cxl_stop_trace_psl9(struct cxl *adapter)
{
	int traceid;
	u64 trace_state, trace_mask;
	struct pci_dev *dev = to_pci_dev(adapter->dev.parent);

	/* read each tracearray state and issue mmio to stop them is needed */
	for (traceid = 0; traceid <= CXL_PSL9_TRACEID_MAX; ++traceid) {
		trace_state = cxl_p1_read(adapter, CXL_PSL9_CTCCFG);
		trace_mask = (0x3ULL << (62 - traceid * 2));
		trace_state = (trace_state & trace_mask) >> (62 - traceid * 2);
		dev_dbg(&dev->dev, "cxl: Traceid-%d trace_state=0x%0llX\n",
			traceid, trace_state);

		/* issue mmio if the trace array isn't in FIN state */
		if (trace_state != CXL_PSL9_TRACESTATE_FIN)
			cxl_p1_write(adapter, CXL_PSL9_TRACECFG,
				     0x8400000000000000ULL | traceid);
	}
}