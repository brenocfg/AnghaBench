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
struct altera_pcie {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RP_TX_EOP ; 
 int /*<<< orphan*/  RP_TX_SOP ; 
 int /*<<< orphan*/  s10_tlp_write_tx (struct altera_pcie*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void s10_tlp_write_packet(struct altera_pcie *pcie, u32 *headers,
				 u32 data, bool dummy)
{
	s10_tlp_write_tx(pcie, headers[0], RP_TX_SOP);
	s10_tlp_write_tx(pcie, headers[1], 0);
	s10_tlp_write_tx(pcie, headers[2], 0);
	s10_tlp_write_tx(pcie, data, RP_TX_EOP);
}