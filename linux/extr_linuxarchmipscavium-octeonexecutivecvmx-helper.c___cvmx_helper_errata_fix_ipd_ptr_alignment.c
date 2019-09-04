#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int en; } ;
union cvmx_gmxx_prtx_cfg {int u64; TYPE_3__ s; } ;
struct TYPE_6__ {scalar_t__ addr; int size; int i; void* pool; } ;
union cvmx_buf_ptr {int u64; TYPE_1__ s; } ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  cvmx_wqe_t ;
struct TYPE_7__ {int segs; int total_bytes; int gather; scalar_t__ dontfree; } ;
struct TYPE_9__ {TYPE_2__ s; scalar_t__ u64; } ;
typedef  TYPE_4__ cvmx_pko_command_word0_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_ASXX_PRT_LOOP (int) ; 
 int /*<<< orphan*/  CVMX_ASXX_RX_PRT_EN (int) ; 
 int /*<<< orphan*/  CVMX_ASXX_TX_PRT_EN (int) ; 
 void* CVMX_FPA_PACKET_POOL ; 
 int CVMX_FPA_PACKET_POOL_SIZE ; 
 void* CVMX_FPA_WQE_POOL ; 
 int /*<<< orphan*/  CVMX_GMXX_PRTX_CFG (int,int) ; 
 int /*<<< orphan*/  CVMX_GMXX_RXX_FRM_MAX (int,int) ; 
 int /*<<< orphan*/  CVMX_GMXX_RXX_JABBER (int,int) ; 
 int CVMX_HELPER_FIRST_MBUFF_SKIP ; 
 int CVMX_HELPER_NOT_FIRST_MBUFF_SKIP ; 
 int /*<<< orphan*/  CVMX_IPD_PTR_COUNT ; 
 int /*<<< orphan*/  CVMX_PKO_LOCK_CMD_QUEUE ; 
 int /*<<< orphan*/  CVMX_POW_WAIT ; 
 int /*<<< orphan*/  CVMX_SYNC ; 
 int /*<<< orphan*/  __delay (unsigned long long) ; 
 int /*<<< orphan*/  cvmx_dprintf (char*) ; 
 int /*<<< orphan*/  cvmx_fpa_alloc (void*) ; 
 int /*<<< orphan*/  cvmx_helper_free_packet_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cvmx_helper_rgmii_internal_loopback (int /*<<< orphan*/ ) ; 
 scalar_t__ cvmx_phys_to_ptr (scalar_t__) ; 
 int /*<<< orphan*/  cvmx_pko_get_base_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_pko_send_packet_finish (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__,union cvmx_buf_ptr,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_pko_send_packet_prepare (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cvmx_pow_work_request_sync (int /*<<< orphan*/ ) ; 
 void* cvmx_ptr_to_phys (int /*<<< orphan*/ ) ; 
 void* cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int) ; 

int __cvmx_helper_errata_fix_ipd_ptr_alignment(void)
{
#define FIX_IPD_FIRST_BUFF_PAYLOAD_BYTES \
     (CVMX_FPA_PACKET_POOL_SIZE-8-CVMX_HELPER_FIRST_MBUFF_SKIP)
#define FIX_IPD_NON_FIRST_BUFF_PAYLOAD_BYTES \
	(CVMX_FPA_PACKET_POOL_SIZE-8-CVMX_HELPER_NOT_FIRST_MBUFF_SKIP)
#define FIX_IPD_OUTPORT 0
	/* Ports 0-15 are interface 0, 16-31 are interface 1 */
#define INTERFACE(port) (port >> 4)
#define INDEX(port) (port & 0xf)
	uint64_t *p64;
	cvmx_pko_command_word0_t pko_command;
	union cvmx_buf_ptr g_buffer, pkt_buffer;
	cvmx_wqe_t *work;
	int size, num_segs = 0, wqe_pcnt, pkt_pcnt;
	union cvmx_gmxx_prtx_cfg gmx_cfg;
	int retry_cnt;
	int retry_loop_cnt;
	int i;

	/* Save values for restore at end */
	uint64_t prtx_cfg =
	    cvmx_read_csr(CVMX_GMXX_PRTX_CFG
			  (INDEX(FIX_IPD_OUTPORT), INTERFACE(FIX_IPD_OUTPORT)));
	uint64_t tx_ptr_en =
	    cvmx_read_csr(CVMX_ASXX_TX_PRT_EN(INTERFACE(FIX_IPD_OUTPORT)));
	uint64_t rx_ptr_en =
	    cvmx_read_csr(CVMX_ASXX_RX_PRT_EN(INTERFACE(FIX_IPD_OUTPORT)));
	uint64_t rxx_jabber =
	    cvmx_read_csr(CVMX_GMXX_RXX_JABBER
			  (INDEX(FIX_IPD_OUTPORT), INTERFACE(FIX_IPD_OUTPORT)));
	uint64_t frame_max =
	    cvmx_read_csr(CVMX_GMXX_RXX_FRM_MAX
			  (INDEX(FIX_IPD_OUTPORT), INTERFACE(FIX_IPD_OUTPORT)));

	/* Configure port to gig FDX as required for loopback mode */
	cvmx_helper_rgmii_internal_loopback(FIX_IPD_OUTPORT);

	/*
	 * Disable reception on all ports so if traffic is present it
	 * will not interfere.
	 */
	cvmx_write_csr(CVMX_ASXX_RX_PRT_EN(INTERFACE(FIX_IPD_OUTPORT)), 0);

	__delay(100000000ull);

	for (retry_loop_cnt = 0; retry_loop_cnt < 10; retry_loop_cnt++) {
		retry_cnt = 100000;
		wqe_pcnt = cvmx_read_csr(CVMX_IPD_PTR_COUNT);
		pkt_pcnt = (wqe_pcnt >> 7) & 0x7f;
		wqe_pcnt &= 0x7f;

		num_segs = (2 + pkt_pcnt - wqe_pcnt) & 3;

		if (num_segs == 0)
			goto fix_ipd_exit;

		num_segs += 1;

		size =
		    FIX_IPD_FIRST_BUFF_PAYLOAD_BYTES +
		    ((num_segs - 1) * FIX_IPD_NON_FIRST_BUFF_PAYLOAD_BYTES) -
		    (FIX_IPD_NON_FIRST_BUFF_PAYLOAD_BYTES / 2);

		cvmx_write_csr(CVMX_ASXX_PRT_LOOP(INTERFACE(FIX_IPD_OUTPORT)),
			       1 << INDEX(FIX_IPD_OUTPORT));
		CVMX_SYNC;

		g_buffer.u64 = 0;
		g_buffer.s.addr =
		    cvmx_ptr_to_phys(cvmx_fpa_alloc(CVMX_FPA_WQE_POOL));
		if (g_buffer.s.addr == 0) {
			cvmx_dprintf("WARNING: FIX_IPD_PTR_ALIGNMENT "
				     "buffer allocation failure.\n");
			goto fix_ipd_exit;
		}

		g_buffer.s.pool = CVMX_FPA_WQE_POOL;
		g_buffer.s.size = num_segs;

		pkt_buffer.u64 = 0;
		pkt_buffer.s.addr =
		    cvmx_ptr_to_phys(cvmx_fpa_alloc(CVMX_FPA_PACKET_POOL));
		if (pkt_buffer.s.addr == 0) {
			cvmx_dprintf("WARNING: FIX_IPD_PTR_ALIGNMENT "
				     "buffer allocation failure.\n");
			goto fix_ipd_exit;
		}
		pkt_buffer.s.i = 1;
		pkt_buffer.s.pool = CVMX_FPA_PACKET_POOL;
		pkt_buffer.s.size = FIX_IPD_FIRST_BUFF_PAYLOAD_BYTES;

		p64 = (uint64_t *) cvmx_phys_to_ptr(pkt_buffer.s.addr);
		p64[0] = 0xffffffffffff0000ull;
		p64[1] = 0x08004510ull;
		p64[2] = ((uint64_t) (size - 14) << 48) | 0x5ae740004000ull;
		p64[3] = 0x3a5fc0a81073c0a8ull;

		for (i = 0; i < num_segs; i++) {
			if (i > 0)
				pkt_buffer.s.size =
				    FIX_IPD_NON_FIRST_BUFF_PAYLOAD_BYTES;

			if (i == (num_segs - 1))
				pkt_buffer.s.i = 0;

			*(uint64_t *) cvmx_phys_to_ptr(g_buffer.s.addr +
						       8 * i) = pkt_buffer.u64;
		}

		/* Build the PKO command */
		pko_command.u64 = 0;
		pko_command.s.segs = num_segs;
		pko_command.s.total_bytes = size;
		pko_command.s.dontfree = 0;
		pko_command.s.gather = 1;

		gmx_cfg.u64 =
		    cvmx_read_csr(CVMX_GMXX_PRTX_CFG
				  (INDEX(FIX_IPD_OUTPORT),
				   INTERFACE(FIX_IPD_OUTPORT)));
		gmx_cfg.s.en = 1;
		cvmx_write_csr(CVMX_GMXX_PRTX_CFG
			       (INDEX(FIX_IPD_OUTPORT),
				INTERFACE(FIX_IPD_OUTPORT)), gmx_cfg.u64);
		cvmx_write_csr(CVMX_ASXX_TX_PRT_EN(INTERFACE(FIX_IPD_OUTPORT)),
			       1 << INDEX(FIX_IPD_OUTPORT));
		cvmx_write_csr(CVMX_ASXX_RX_PRT_EN(INTERFACE(FIX_IPD_OUTPORT)),
			       1 << INDEX(FIX_IPD_OUTPORT));

		cvmx_write_csr(CVMX_GMXX_RXX_JABBER
			       (INDEX(FIX_IPD_OUTPORT),
				INTERFACE(FIX_IPD_OUTPORT)), 65392 - 14 - 4);
		cvmx_write_csr(CVMX_GMXX_RXX_FRM_MAX
			       (INDEX(FIX_IPD_OUTPORT),
				INTERFACE(FIX_IPD_OUTPORT)), 65392 - 14 - 4);

		cvmx_pko_send_packet_prepare(FIX_IPD_OUTPORT,
					     cvmx_pko_get_base_queue
					     (FIX_IPD_OUTPORT),
					     CVMX_PKO_LOCK_CMD_QUEUE);
		cvmx_pko_send_packet_finish(FIX_IPD_OUTPORT,
					    cvmx_pko_get_base_queue
					    (FIX_IPD_OUTPORT), pko_command,
					    g_buffer, CVMX_PKO_LOCK_CMD_QUEUE);

		CVMX_SYNC;

		do {
			work = cvmx_pow_work_request_sync(CVMX_POW_WAIT);
			retry_cnt--;
		} while ((work == NULL) && (retry_cnt > 0));

		if (!retry_cnt)
			cvmx_dprintf("WARNING: FIX_IPD_PTR_ALIGNMENT "
				     "get_work() timeout occurred.\n");

		/* Free packet */
		if (work)
			cvmx_helper_free_packet_data(work);
	}

fix_ipd_exit:

	/* Return CSR configs to saved values */
	cvmx_write_csr(CVMX_GMXX_PRTX_CFG
		       (INDEX(FIX_IPD_OUTPORT), INTERFACE(FIX_IPD_OUTPORT)),
		       prtx_cfg);
	cvmx_write_csr(CVMX_ASXX_TX_PRT_EN(INTERFACE(FIX_IPD_OUTPORT)),
		       tx_ptr_en);
	cvmx_write_csr(CVMX_ASXX_RX_PRT_EN(INTERFACE(FIX_IPD_OUTPORT)),
		       rx_ptr_en);
	cvmx_write_csr(CVMX_GMXX_RXX_JABBER
		       (INDEX(FIX_IPD_OUTPORT), INTERFACE(FIX_IPD_OUTPORT)),
		       rxx_jabber);
	cvmx_write_csr(CVMX_GMXX_RXX_FRM_MAX
		       (INDEX(FIX_IPD_OUTPORT), INTERFACE(FIX_IPD_OUTPORT)),
		       frame_max);
	cvmx_write_csr(CVMX_ASXX_PRT_LOOP(INTERFACE(FIX_IPD_OUTPORT)), 0);

	CVMX_SYNC;
	if (num_segs)
		cvmx_dprintf("WARNING: FIX_IPD_PTR_ALIGNMENT failed.\n");

	return !!num_segs;

}