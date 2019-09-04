#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int pid; int rate_lim; } ;
union cvmx_pko_mem_port_rate1 {scalar_t__ u64; TYPE_2__ s; } ;
struct TYPE_4__ {int pid; int rate_pkt; int rate_word; } ;
union cvmx_pko_mem_port_rate0 {scalar_t__ u64; TYPE_1__ s; } ;
typedef  int uint64_t ;
struct TYPE_6__ {int cpu_clock_hz; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_PKO_MEM_PORT_RATE0 ; 
 int /*<<< orphan*/  CVMX_PKO_MEM_PORT_RATE1 ; 
 TYPE_3__* cvmx_sysinfo_get () ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,scalar_t__) ; 

int cvmx_pko_rate_limit_bits(int port, uint64_t bits_s, int burst)
{
	union cvmx_pko_mem_port_rate0 pko_mem_port_rate0;
	union cvmx_pko_mem_port_rate1 pko_mem_port_rate1;
	uint64_t clock_rate = cvmx_sysinfo_get()->cpu_clock_hz;
	uint64_t tokens_per_bit = clock_rate * 16 / bits_s;

	pko_mem_port_rate0.u64 = 0;
	pko_mem_port_rate0.s.pid = port;
	/*
	 * Each packet has a 12 bytes of interframe gap, an 8 byte
	 * preamble, and a 4 byte CRC. These are not included in the
	 * per word count. Multiply by 8 to covert to bits and divide
	 * by 256 for limit granularity.
	 */
	pko_mem_port_rate0.s.rate_pkt = (12 + 8 + 4) * 8 * tokens_per_bit / 256;
	/* Each 8 byte word has 64bits */
	pko_mem_port_rate0.s.rate_word = 64 * tokens_per_bit;

	pko_mem_port_rate1.u64 = 0;
	pko_mem_port_rate1.s.pid = port;
	pko_mem_port_rate1.s.rate_lim = tokens_per_bit * burst / 256;

	cvmx_write_csr(CVMX_PKO_MEM_PORT_RATE0, pko_mem_port_rate0.u64);
	cvmx_write_csr(CVMX_PKO_MEM_PORT_RATE1, pko_mem_port_rate1.u64);
	return 0;
}