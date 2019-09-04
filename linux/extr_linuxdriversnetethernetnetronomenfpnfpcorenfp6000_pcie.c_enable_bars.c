#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct resource {int dummy; } ;
struct nfp_bar {int index; int /*<<< orphan*/ * iomem; scalar_t__ bitsize; int /*<<< orphan*/  refcnt; scalar_t__ base; scalar_t__ mask; struct nfp6000_pcie* nfp; scalar_t__ barcfg; struct resource* resource; } ;
struct TYPE_8__ {int /*<<< orphan*/ ** expl; int /*<<< orphan*/ * em; int /*<<< orphan*/ * csr; } ;
struct TYPE_6__ {int master_id; int signal_ref; TYPE_1__* group; int /*<<< orphan*/ * data; int /*<<< orphan*/  mutex; } ;
struct nfp6000_pcie {int bars; int /*<<< orphan*/  dev; struct nfp_bar* bar; TYPE_4__ iomem; TYPE_2__ expl; TYPE_3__* pdev; } ;
typedef  int /*<<< orphan*/  status_msg ;
struct TYPE_7__ {scalar_t__ device; int devfn; struct resource* resource; } ;
struct TYPE_5__ {int* free; int /*<<< orphan*/ * addr; scalar_t__ bitsize; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct nfp_bar*) ; 
 int EINVAL ; 
 int IORESOURCE_MEM ; 
 int NFP_CPP_INTERFACE_UNIT_of (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFP_CPP_TARGET_ISLAND_XPB ; 
 int NFP_PCIE_BAR (int) ; 
 int const NFP_PCIE_BAR_PCIE2CPP_LengthSelect_32BIT ; 
 int const NFP_PCIE_BAR_PCIE2CPP_MapType (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFP_PCIE_BAR_PCIE2CPP_MapType_BULK ; 
 int /*<<< orphan*/  NFP_PCIE_BAR_PCIE2CPP_MapType_EXPLICIT0 ; 
 int /*<<< orphan*/  NFP_PCIE_BAR_PCIE2CPP_MapType_EXPLICIT1 ; 
 int /*<<< orphan*/  NFP_PCIE_BAR_PCIE2CPP_MapType_EXPLICIT2 ; 
 int /*<<< orphan*/  NFP_PCIE_BAR_PCIE2CPP_MapType_EXPLICIT3 ; 
 int /*<<< orphan*/  NFP_PCIE_BAR_PCIE2CPP_MapType_GENERAL ; 
 int const NFP_PCIE_BAR_PCIE2CPP_Target_BaseAddress (int /*<<< orphan*/ ) ; 
 int NFP_PCIE_EM ; 
 int NFP_PCIE_EXPLICIT_BARS ; 
 int NFP_PCIE_SRAM ; 
 scalar_t__ NFP_PCI_MIN_MAP_SIZE ; 
 scalar_t__ PCI_DEVICE_ID_NETRONOME_NFP4000 ; 
 scalar_t__ PCI_DEVICE_ID_NETRONOME_NFP6000 ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bar_cmp ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,char*,int,int) ; 
 scalar_t__ fls (scalar_t__) ; 
 void* ioremap_nocache (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfp6000_bar_write (struct nfp6000_pcie*,struct nfp_bar*,int const) ; 
 scalar_t__ nfp_bar_resource_len (struct nfp_bar*) ; 
 int /*<<< orphan*/  nfp_bar_resource_start (struct nfp_bar*) ; 
 int resource_type (struct resource*) ; 
 int snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  sort (struct nfp_bar*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int enable_bars(struct nfp6000_pcie *nfp, u16 interface)
{
	const u32 barcfg_msix_general =
		NFP_PCIE_BAR_PCIE2CPP_MapType(
			NFP_PCIE_BAR_PCIE2CPP_MapType_GENERAL) |
		NFP_PCIE_BAR_PCIE2CPP_LengthSelect_32BIT;
	const u32 barcfg_msix_xpb =
		NFP_PCIE_BAR_PCIE2CPP_MapType(
			NFP_PCIE_BAR_PCIE2CPP_MapType_BULK) |
		NFP_PCIE_BAR_PCIE2CPP_LengthSelect_32BIT |
		NFP_PCIE_BAR_PCIE2CPP_Target_BaseAddress(
			NFP_CPP_TARGET_ISLAND_XPB);
	const u32 barcfg_explicit[4] = {
		NFP_PCIE_BAR_PCIE2CPP_MapType(
			NFP_PCIE_BAR_PCIE2CPP_MapType_EXPLICIT0),
		NFP_PCIE_BAR_PCIE2CPP_MapType(
			NFP_PCIE_BAR_PCIE2CPP_MapType_EXPLICIT1),
		NFP_PCIE_BAR_PCIE2CPP_MapType(
			NFP_PCIE_BAR_PCIE2CPP_MapType_EXPLICIT2),
		NFP_PCIE_BAR_PCIE2CPP_MapType(
			NFP_PCIE_BAR_PCIE2CPP_MapType_EXPLICIT3),
	};
	char status_msg[196] = {};
	struct nfp_bar *bar;
	int i, bars_free;
	int expl_groups;
	char *msg, *end;

	msg = status_msg +
		snprintf(status_msg, sizeof(status_msg) - 1, "RESERVED BARs: ");
	end = status_msg + sizeof(status_msg) - 1;

	bar = &nfp->bar[0];
	for (i = 0; i < ARRAY_SIZE(nfp->bar); i++, bar++) {
		struct resource *res;

		res = &nfp->pdev->resource[(i >> 3) * 2];

		/* Skip over BARs that are not IORESOURCE_MEM */
		if (!(resource_type(res) & IORESOURCE_MEM)) {
			bar--;
			continue;
		}

		bar->resource = res;
		bar->barcfg = 0;

		bar->nfp = nfp;
		bar->index = i;
		bar->mask = nfp_bar_resource_len(bar) - 1;
		bar->bitsize = fls(bar->mask);
		bar->base = 0;
		bar->iomem = NULL;
	}

	nfp->bars = bar - &nfp->bar[0];
	if (nfp->bars < 8) {
		dev_err(nfp->dev, "No usable BARs found!\n");
		return -EINVAL;
	}

	bars_free = nfp->bars;

	/* Convert unit ID (0..3) to signal master/data master ID (0x40..0x70)
	 */
	mutex_init(&nfp->expl.mutex);

	nfp->expl.master_id = ((NFP_CPP_INTERFACE_UNIT_of(interface) & 3) + 4)
		<< 4;
	nfp->expl.signal_ref = 0x10;

	/* Configure, and lock, BAR0.0 for General Target use (MSI-X SRAM) */
	bar = &nfp->bar[0];
	if (nfp_bar_resource_len(bar) >= NFP_PCI_MIN_MAP_SIZE)
		bar->iomem = ioremap_nocache(nfp_bar_resource_start(bar),
					     nfp_bar_resource_len(bar));
	if (bar->iomem) {
		msg += snprintf(msg, end - msg,	"0.0: General/MSI-X SRAM, ");
		atomic_inc(&bar->refcnt);
		bars_free--;

		nfp6000_bar_write(nfp, bar, barcfg_msix_general);

		nfp->expl.data = bar->iomem + NFP_PCIE_SRAM + 0x1000;

		if (nfp->pdev->device == PCI_DEVICE_ID_NETRONOME_NFP4000 ||
		    nfp->pdev->device == PCI_DEVICE_ID_NETRONOME_NFP6000) {
			nfp->iomem.csr = bar->iomem + NFP_PCIE_BAR(0);
		} else {
			int pf = nfp->pdev->devfn & 7;

			nfp->iomem.csr = bar->iomem + NFP_PCIE_BAR(pf);
		}
		nfp->iomem.em = bar->iomem + NFP_PCIE_EM;
	}

	if (nfp->pdev->device == PCI_DEVICE_ID_NETRONOME_NFP4000 ||
	    nfp->pdev->device == PCI_DEVICE_ID_NETRONOME_NFP6000)
		expl_groups = 4;
	else
		expl_groups = 1;

	/* Configure, and lock, BAR0.1 for PCIe XPB (MSI-X PBA) */
	bar = &nfp->bar[1];
	msg += snprintf(msg, end - msg, "0.1: PCIe XPB/MSI-X PBA, ");
	atomic_inc(&bar->refcnt);
	bars_free--;

	nfp6000_bar_write(nfp, bar, barcfg_msix_xpb);

	/* Use BAR0.4..BAR0.7 for EXPL IO */
	for (i = 0; i < 4; i++) {
		int j;

		if (i >= NFP_PCIE_EXPLICIT_BARS || i >= expl_groups) {
			nfp->expl.group[i].bitsize = 0;
			continue;
		}

		bar = &nfp->bar[4 + i];
		bar->iomem = ioremap_nocache(nfp_bar_resource_start(bar),
					     nfp_bar_resource_len(bar));
		if (bar->iomem) {
			msg += snprintf(msg, end - msg,
					"0.%d: Explicit%d, ", 4 + i, i);
			atomic_inc(&bar->refcnt);
			bars_free--;

			nfp->expl.group[i].bitsize = bar->bitsize;
			nfp->expl.group[i].addr = bar->iomem;
			nfp6000_bar_write(nfp, bar, barcfg_explicit[i]);

			for (j = 0; j < 4; j++)
				nfp->expl.group[i].free[j] = true;
		}
		nfp->iomem.expl[i] = bar->iomem;
	}

	/* Sort bars by bit size - use the smallest possible first. */
	sort(&nfp->bar[0], nfp->bars, sizeof(nfp->bar[0]),
	     bar_cmp, NULL);

	dev_info(nfp->dev, "%sfree: %d/%d\n", status_msg, bars_free, nfp->bars);

	return 0;
}