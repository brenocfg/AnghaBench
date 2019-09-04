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
struct TYPE_2__ {int hg2cc; int hg2fld; int undat; int uneop; int unsop; int bad_term; int bad_seq; int rem_fault; int loc_fault; int pause_drp; int ovrerr; int skperr; int rcverr; int jabber; int carext; int niberr; int alnerr; int maxerr; int minerr; } ;
union cvmx_gmxx_rxx_int_en {scalar_t__ u64; TYPE_1__ s; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_GMXX_RXX_INT_EN (int,int) ; 
 int /*<<< orphan*/  CVMX_GMXX_RXX_INT_REG (int,int) ; 
 int /*<<< orphan*/  OCTEON_CN30XX ; 
 int /*<<< orphan*/  OCTEON_CN31XX ; 
 int /*<<< orphan*/  OCTEON_CN38XX ; 
 int /*<<< orphan*/  OCTEON_CN50XX ; 
 int /*<<< orphan*/  OCTEON_CN52XX ; 
 int /*<<< orphan*/  OCTEON_CN56XX ; 
 int /*<<< orphan*/  OCTEON_CN58XX ; 
 scalar_t__ OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 scalar_t__ cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,scalar_t__) ; 

void __cvmx_interrupt_gmxx_rxx_int_en_enable(int index, int block)
{
	union cvmx_gmxx_rxx_int_en gmx_rx_int_en;
	cvmx_write_csr(CVMX_GMXX_RXX_INT_REG(index, block),
		       cvmx_read_csr(CVMX_GMXX_RXX_INT_REG(index, block)));
	gmx_rx_int_en.u64 = 0;
	if (OCTEON_IS_MODEL(OCTEON_CN56XX)) {
		/* Skipping gmx_rx_int_en.s.reserved_29_63 */
		gmx_rx_int_en.s.hg2cc = 1;
		gmx_rx_int_en.s.hg2fld = 1;
		gmx_rx_int_en.s.undat = 1;
		gmx_rx_int_en.s.uneop = 1;
		gmx_rx_int_en.s.unsop = 1;
		gmx_rx_int_en.s.bad_term = 1;
		gmx_rx_int_en.s.bad_seq = 1;
		gmx_rx_int_en.s.rem_fault = 1;
		gmx_rx_int_en.s.loc_fault = 1;
		gmx_rx_int_en.s.pause_drp = 1;
		/* Skipping gmx_rx_int_en.s.reserved_16_18 */
		/*gmx_rx_int_en.s.ifgerr = 1; */
		/*gmx_rx_int_en.s.coldet = 1; // Collision detect */
		/*gmx_rx_int_en.s.falerr = 1; // False carrier error or extend error after slottime */
		/*gmx_rx_int_en.s.rsverr = 1; // RGMII reserved opcodes */
		/*gmx_rx_int_en.s.pcterr = 1; // Bad Preamble / Protocol */
		gmx_rx_int_en.s.ovrerr = 1;
		/* Skipping gmx_rx_int_en.s.reserved_9_9 */
		gmx_rx_int_en.s.skperr = 1;
		gmx_rx_int_en.s.rcverr = 1;
		/* Skipping gmx_rx_int_en.s.reserved_5_6 */
		/*gmx_rx_int_en.s.fcserr = 1; // FCS errors are handled when we get work */
		gmx_rx_int_en.s.jabber = 1;
		/* Skipping gmx_rx_int_en.s.reserved_2_2 */
		gmx_rx_int_en.s.carext = 1;
		/* Skipping gmx_rx_int_en.s.reserved_0_0 */
	}
	if (OCTEON_IS_MODEL(OCTEON_CN30XX)) {
		/* Skipping gmx_rx_int_en.s.reserved_19_63 */
		/*gmx_rx_int_en.s.phy_dupx = 1; */
		/*gmx_rx_int_en.s.phy_spd = 1; */
		/*gmx_rx_int_en.s.phy_link = 1; */
		/*gmx_rx_int_en.s.ifgerr = 1; */
		/*gmx_rx_int_en.s.coldet = 1; // Collision detect */
		/*gmx_rx_int_en.s.falerr = 1; // False carrier error or extend error after slottime */
		/*gmx_rx_int_en.s.rsverr = 1; // RGMII reserved opcodes */
		/*gmx_rx_int_en.s.pcterr = 1; // Bad Preamble / Protocol */
		gmx_rx_int_en.s.ovrerr = 1;
		gmx_rx_int_en.s.niberr = 1;
		gmx_rx_int_en.s.skperr = 1;
		gmx_rx_int_en.s.rcverr = 1;
		/*gmx_rx_int_en.s.lenerr = 1; // Length errors are handled when we get work */
		gmx_rx_int_en.s.alnerr = 1;
		/*gmx_rx_int_en.s.fcserr = 1; // FCS errors are handled when we get work */
		gmx_rx_int_en.s.jabber = 1;
		gmx_rx_int_en.s.maxerr = 1;
		gmx_rx_int_en.s.carext = 1;
		gmx_rx_int_en.s.minerr = 1;
	}
	if (OCTEON_IS_MODEL(OCTEON_CN50XX)) {
		/* Skipping gmx_rx_int_en.s.reserved_20_63 */
		gmx_rx_int_en.s.pause_drp = 1;
		/*gmx_rx_int_en.s.phy_dupx = 1; */
		/*gmx_rx_int_en.s.phy_spd = 1; */
		/*gmx_rx_int_en.s.phy_link = 1; */
		/*gmx_rx_int_en.s.ifgerr = 1; */
		/*gmx_rx_int_en.s.coldet = 1; // Collision detect */
		/*gmx_rx_int_en.s.falerr = 1; // False carrier error or extend error after slottime */
		/*gmx_rx_int_en.s.rsverr = 1; // RGMII reserved opcodes */
		/*gmx_rx_int_en.s.pcterr = 1; // Bad Preamble / Protocol */
		gmx_rx_int_en.s.ovrerr = 1;
		gmx_rx_int_en.s.niberr = 1;
		gmx_rx_int_en.s.skperr = 1;
		gmx_rx_int_en.s.rcverr = 1;
		/* Skipping gmx_rx_int_en.s.reserved_6_6 */
		gmx_rx_int_en.s.alnerr = 1;
		/*gmx_rx_int_en.s.fcserr = 1; // FCS errors are handled when we get work */
		gmx_rx_int_en.s.jabber = 1;
		/* Skipping gmx_rx_int_en.s.reserved_2_2 */
		gmx_rx_int_en.s.carext = 1;
		/* Skipping gmx_rx_int_en.s.reserved_0_0 */
	}
	if (OCTEON_IS_MODEL(OCTEON_CN38XX)) {
		/* Skipping gmx_rx_int_en.s.reserved_19_63 */
		/*gmx_rx_int_en.s.phy_dupx = 1; */
		/*gmx_rx_int_en.s.phy_spd = 1; */
		/*gmx_rx_int_en.s.phy_link = 1; */
		/*gmx_rx_int_en.s.ifgerr = 1; */
		/*gmx_rx_int_en.s.coldet = 1; // Collision detect */
		/*gmx_rx_int_en.s.falerr = 1; // False carrier error or extend error after slottime */
		/*gmx_rx_int_en.s.rsverr = 1; // RGMII reserved opcodes */
		/*gmx_rx_int_en.s.pcterr = 1; // Bad Preamble / Protocol */
		gmx_rx_int_en.s.ovrerr = 1;
		gmx_rx_int_en.s.niberr = 1;
		gmx_rx_int_en.s.skperr = 1;
		gmx_rx_int_en.s.rcverr = 1;
		/*gmx_rx_int_en.s.lenerr = 1; // Length errors are handled when we get work */
		gmx_rx_int_en.s.alnerr = 1;
		/*gmx_rx_int_en.s.fcserr = 1; // FCS errors are handled when we get work */
		gmx_rx_int_en.s.jabber = 1;
		gmx_rx_int_en.s.maxerr = 1;
		gmx_rx_int_en.s.carext = 1;
		gmx_rx_int_en.s.minerr = 1;
	}
	if (OCTEON_IS_MODEL(OCTEON_CN31XX)) {
		/* Skipping gmx_rx_int_en.s.reserved_19_63 */
		/*gmx_rx_int_en.s.phy_dupx = 1; */
		/*gmx_rx_int_en.s.phy_spd = 1; */
		/*gmx_rx_int_en.s.phy_link = 1; */
		/*gmx_rx_int_en.s.ifgerr = 1; */
		/*gmx_rx_int_en.s.coldet = 1; // Collision detect */
		/*gmx_rx_int_en.s.falerr = 1; // False carrier error or extend error after slottime */
		/*gmx_rx_int_en.s.rsverr = 1; // RGMII reserved opcodes */
		/*gmx_rx_int_en.s.pcterr = 1; // Bad Preamble / Protocol */
		gmx_rx_int_en.s.ovrerr = 1;
		gmx_rx_int_en.s.niberr = 1;
		gmx_rx_int_en.s.skperr = 1;
		gmx_rx_int_en.s.rcverr = 1;
		/*gmx_rx_int_en.s.lenerr = 1; // Length errors are handled when we get work */
		gmx_rx_int_en.s.alnerr = 1;
		/*gmx_rx_int_en.s.fcserr = 1; // FCS errors are handled when we get work */
		gmx_rx_int_en.s.jabber = 1;
		gmx_rx_int_en.s.maxerr = 1;
		gmx_rx_int_en.s.carext = 1;
		gmx_rx_int_en.s.minerr = 1;
	}
	if (OCTEON_IS_MODEL(OCTEON_CN58XX)) {
		/* Skipping gmx_rx_int_en.s.reserved_20_63 */
		gmx_rx_int_en.s.pause_drp = 1;
		/*gmx_rx_int_en.s.phy_dupx = 1; */
		/*gmx_rx_int_en.s.phy_spd = 1; */
		/*gmx_rx_int_en.s.phy_link = 1; */
		/*gmx_rx_int_en.s.ifgerr = 1; */
		/*gmx_rx_int_en.s.coldet = 1; // Collision detect */
		/*gmx_rx_int_en.s.falerr = 1; // False carrier error or extend error after slottime */
		/*gmx_rx_int_en.s.rsverr = 1; // RGMII reserved opcodes */
		/*gmx_rx_int_en.s.pcterr = 1; // Bad Preamble / Protocol */
		gmx_rx_int_en.s.ovrerr = 1;
		gmx_rx_int_en.s.niberr = 1;
		gmx_rx_int_en.s.skperr = 1;
		gmx_rx_int_en.s.rcverr = 1;
		/*gmx_rx_int_en.s.lenerr = 1; // Length errors are handled when we get work */
		gmx_rx_int_en.s.alnerr = 1;
		/*gmx_rx_int_en.s.fcserr = 1; // FCS errors are handled when we get work */
		gmx_rx_int_en.s.jabber = 1;
		gmx_rx_int_en.s.maxerr = 1;
		gmx_rx_int_en.s.carext = 1;
		gmx_rx_int_en.s.minerr = 1;
	}
	if (OCTEON_IS_MODEL(OCTEON_CN52XX)) {
		/* Skipping gmx_rx_int_en.s.reserved_29_63 */
		gmx_rx_int_en.s.hg2cc = 1;
		gmx_rx_int_en.s.hg2fld = 1;
		gmx_rx_int_en.s.undat = 1;
		gmx_rx_int_en.s.uneop = 1;
		gmx_rx_int_en.s.unsop = 1;
		gmx_rx_int_en.s.bad_term = 1;
		gmx_rx_int_en.s.bad_seq = 0;
		gmx_rx_int_en.s.rem_fault = 1;
		gmx_rx_int_en.s.loc_fault = 0;
		gmx_rx_int_en.s.pause_drp = 1;
		/* Skipping gmx_rx_int_en.s.reserved_16_18 */
		/*gmx_rx_int_en.s.ifgerr = 1; */
		/*gmx_rx_int_en.s.coldet = 1; // Collision detect */
		/*gmx_rx_int_en.s.falerr = 1; // False carrier error or extend error after slottime */
		/*gmx_rx_int_en.s.rsverr = 1; // RGMII reserved opcodes */
		/*gmx_rx_int_en.s.pcterr = 1; // Bad Preamble / Protocol */
		gmx_rx_int_en.s.ovrerr = 1;
		/* Skipping gmx_rx_int_en.s.reserved_9_9 */
		gmx_rx_int_en.s.skperr = 1;
		gmx_rx_int_en.s.rcverr = 1;
		/* Skipping gmx_rx_int_en.s.reserved_5_6 */
		/*gmx_rx_int_en.s.fcserr = 1; // FCS errors are handled when we get work */
		gmx_rx_int_en.s.jabber = 1;
		/* Skipping gmx_rx_int_en.s.reserved_2_2 */
		gmx_rx_int_en.s.carext = 1;
		/* Skipping gmx_rx_int_en.s.reserved_0_0 */
	}
	cvmx_write_csr(CVMX_GMXX_RXX_INT_EN(index, block), gmx_rx_int_en.u64);
}