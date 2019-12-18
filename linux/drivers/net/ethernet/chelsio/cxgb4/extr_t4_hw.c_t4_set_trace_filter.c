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
typedef  int u32 ;
struct trace_params {int snap_len; int port; int invert; scalar_t__ skip_len; scalar_t__ skip_ofst; scalar_t__ min_len; int* data; int* mask; } ;
struct TYPE_2__ {int /*<<< orphan*/  chip; } ;
struct adapter {TYPE_1__ params; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MPS_TRC_CFG_A ; 
 int MPS_TRC_FILTER0_DONT_CARE_A ; 
 int MPS_TRC_FILTER0_MATCH_A ; 
 int MPS_TRC_FILTER1_MATCH_A ; 
 int MPS_TRC_FILTER_MATCH_CTL_A_A ; 
 int MPS_TRC_FILTER_MATCH_CTL_B_A ; 
 int T5_TFEN_F ; 
 int T5_TFINVERTMATCH_V (int) ; 
 int T5_TFPORT_V (int) ; 
 int TFCAPTUREMAX_V (int) ; 
 int TFEN_F ; 
 int TFINVERTMATCH_V (int) ; 
 scalar_t__ TFLENGTH_M ; 
 int TFLENGTH_V (scalar_t__) ; 
 scalar_t__ TFMINPKTSIZE_M ; 
 int TFMINPKTSIZE_V (scalar_t__) ; 
 scalar_t__ TFOFFSET_M ; 
 int TFOFFSET_V (scalar_t__) ; 
 int TFPORT_V (int) ; 
 int TRACE_LEN ; 
 int TRCMULTIFILTER_F ; 
 scalar_t__ is_t4 (int /*<<< orphan*/ ) ; 
 int t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,int,int) ; 

int t4_set_trace_filter(struct adapter *adap, const struct trace_params *tp,
			int idx, int enable)
{
	int i, ofst = idx * 4;
	u32 data_reg, mask_reg, cfg;

	if (!enable) {
		t4_write_reg(adap, MPS_TRC_FILTER_MATCH_CTL_A_A + ofst, 0);
		return 0;
	}

	cfg = t4_read_reg(adap, MPS_TRC_CFG_A);
	if (cfg & TRCMULTIFILTER_F) {
		/* If multiple tracers are enabled, then maximum
		 * capture size is 2.5KB (FIFO size of a single channel)
		 * minus 2 flits for CPL_TRACE_PKT header.
		 */
		if (tp->snap_len > ((10 * 1024 / 4) - (2 * 8)))
			return -EINVAL;
	} else {
		/* If multiple tracers are disabled, to avoid deadlocks
		 * maximum packet capture size of 9600 bytes is recommended.
		 * Also in this mode, only trace0 can be enabled and running.
		 */
		if (tp->snap_len > 9600 || idx)
			return -EINVAL;
	}

	if (tp->port > (is_t4(adap->params.chip) ? 11 : 19) || tp->invert > 1 ||
	    tp->skip_len > TFLENGTH_M || tp->skip_ofst > TFOFFSET_M ||
	    tp->min_len > TFMINPKTSIZE_M)
		return -EINVAL;

	/* stop the tracer we'll be changing */
	t4_write_reg(adap, MPS_TRC_FILTER_MATCH_CTL_A_A + ofst, 0);

	idx *= (MPS_TRC_FILTER1_MATCH_A - MPS_TRC_FILTER0_MATCH_A);
	data_reg = MPS_TRC_FILTER0_MATCH_A + idx;
	mask_reg = MPS_TRC_FILTER0_DONT_CARE_A + idx;

	for (i = 0; i < TRACE_LEN / 4; i++, data_reg += 4, mask_reg += 4) {
		t4_write_reg(adap, data_reg, tp->data[i]);
		t4_write_reg(adap, mask_reg, ~tp->mask[i]);
	}
	t4_write_reg(adap, MPS_TRC_FILTER_MATCH_CTL_B_A + ofst,
		     TFCAPTUREMAX_V(tp->snap_len) |
		     TFMINPKTSIZE_V(tp->min_len));
	t4_write_reg(adap, MPS_TRC_FILTER_MATCH_CTL_A_A + ofst,
		     TFOFFSET_V(tp->skip_ofst) | TFLENGTH_V(tp->skip_len) |
		     (is_t4(adap->params.chip) ?
		     TFPORT_V(tp->port) | TFEN_F | TFINVERTMATCH_V(tp->invert) :
		     T5_TFPORT_V(tp->port) | T5_TFEN_F |
		     T5_TFINVERTMATCH_V(tp->invert)));

	return 0;
}