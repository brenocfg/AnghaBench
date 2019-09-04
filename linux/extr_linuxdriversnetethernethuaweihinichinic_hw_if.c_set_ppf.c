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
typedef  int /*<<< orphan*/  u32 ;
struct hinic_func_attr {scalar_t__ ppf_idx; int /*<<< orphan*/  func_type; } ;
struct hinic_hwif {struct hinic_func_attr attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  HINIC_CSR_PPF_ELECTION_ADDR (int /*<<< orphan*/ ) ; 
 scalar_t__ HINIC_HWIF_FUNC_IDX (struct hinic_hwif*) ; 
 int /*<<< orphan*/  HINIC_HWIF_PCI_INTF (struct hinic_hwif*) ; 
 int /*<<< orphan*/  HINIC_PPF ; 
 int /*<<< orphan*/  HINIC_PPF_ELECTION_CLEAR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ HINIC_PPF_ELECTION_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HINIC_PPF_ELECTION_SET (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDX ; 
 int /*<<< orphan*/  hinic_hwif_read_reg (struct hinic_hwif*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hinic_hwif_write_reg (struct hinic_hwif*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_ppf(struct hinic_hwif *hwif)
{
	struct hinic_func_attr *attr = &hwif->attr;
	u32 addr, val, ppf_election;

	/* Read Modify Write */
	addr = HINIC_CSR_PPF_ELECTION_ADDR(HINIC_HWIF_PCI_INTF(hwif));

	val = hinic_hwif_read_reg(hwif, addr);
	val = HINIC_PPF_ELECTION_CLEAR(val, IDX);

	ppf_election = HINIC_PPF_ELECTION_SET(HINIC_HWIF_FUNC_IDX(hwif), IDX);

	val |= ppf_election;
	hinic_hwif_write_reg(hwif, addr, val);

	/* check PPF */
	val = hinic_hwif_read_reg(hwif, addr);

	attr->ppf_idx = HINIC_PPF_ELECTION_GET(val, IDX);
	if (attr->ppf_idx == HINIC_HWIF_FUNC_IDX(hwif))
		attr->func_type = HINIC_PPF;
}