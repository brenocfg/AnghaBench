#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct altera_pcie {TYPE_2__* pcie_data; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* tlp_read_pkt ) (struct altera_pcie*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* tlp_write_pkt ) (struct altera_pcie*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int TLP_HDR_SIZE ; 
 int /*<<< orphan*/  get_tlp_header (struct altera_pcie*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct altera_pcie*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int stub2 (struct altera_pcie*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tlp_cfg_dword_read(struct altera_pcie *pcie, u8 bus, u32 devfn,
			      int where, u8 byte_en, u32 *value)
{
	u32 headers[TLP_HDR_SIZE];

	get_tlp_header(pcie, bus, devfn, where, byte_en, true,
		       headers);

	pcie->pcie_data->ops->tlp_write_pkt(pcie, headers, 0, false);

	return pcie->pcie_data->ops->tlp_read_pkt(pcie, value);
}