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
struct lpc_cycle_para {size_t csize; int /*<<< orphan*/  opflags; } ;
struct hisi_lpc_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FG_INCRADDR_LPC ; 
 size_t LPC_MAX_DWIDTH ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 unsigned long hisi_lpc_pio_to_addr (struct hisi_lpc_dev*,unsigned long) ; 
 int /*<<< orphan*/  hisi_lpc_target_out (struct hisi_lpc_dev*,struct lpc_cycle_para*,unsigned long,unsigned char const*,size_t) ; 

__attribute__((used)) static void hisi_lpc_comm_out(void *hostdata, unsigned long pio,
			      u32 val, size_t dwidth)
{
	struct hisi_lpc_dev *lpcdev = hostdata;
	struct lpc_cycle_para iopara;
	const unsigned char *buf;
	unsigned long addr;

	if (!lpcdev || !dwidth || dwidth > LPC_MAX_DWIDTH)
		return;

	val = cpu_to_le32(val);

	buf = (const unsigned char *)&val;
	addr = hisi_lpc_pio_to_addr(lpcdev, pio);

	iopara.opflags = FG_INCRADDR_LPC;
	iopara.csize = dwidth;

	hisi_lpc_target_out(lpcdev, &iopara, addr, buf, dwidth);
}