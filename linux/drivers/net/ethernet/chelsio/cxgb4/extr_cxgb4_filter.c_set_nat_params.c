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
struct TYPE_2__ {int* nat_lip; int* nat_fip; int nat_lport; int nat_fport; scalar_t__ type; } ;
struct filter_entry {TYPE_1__ fs; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ TCB_PDU_HDR_LEN_W ; 
 scalar_t__ TCB_RX_FRAG2_PTR_RAW_W ; 
 scalar_t__ TCB_RX_FRAG3_LEN_RAW_W ; 
 scalar_t__ TCB_RX_FRAG3_START_IDX_OFFSET_RAW_W ; 
 scalar_t__ TCB_SND_UNA_RAW_W ; 
 int /*<<< orphan*/  WORD_MASK ; 
 int /*<<< orphan*/  set_tcb_field (struct adapter*,struct filter_entry*,unsigned int,scalar_t__,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void set_nat_params(struct adapter *adap, struct filter_entry *f,
			   unsigned int tid, bool dip, bool sip, bool dp,
			   bool sp)
{
	if (dip) {
		if (f->fs.type) {
			set_tcb_field(adap, f, tid, TCB_SND_UNA_RAW_W,
				      WORD_MASK, f->fs.nat_lip[15] |
				      f->fs.nat_lip[14] << 8 |
				      f->fs.nat_lip[13] << 16 |
				      f->fs.nat_lip[12] << 24, 1);

			set_tcb_field(adap, f, tid, TCB_SND_UNA_RAW_W + 1,
				      WORD_MASK, f->fs.nat_lip[11] |
				      f->fs.nat_lip[10] << 8 |
				      f->fs.nat_lip[9] << 16 |
				      f->fs.nat_lip[8] << 24, 1);

			set_tcb_field(adap, f, tid, TCB_SND_UNA_RAW_W + 2,
				      WORD_MASK, f->fs.nat_lip[7] |
				      f->fs.nat_lip[6] << 8 |
				      f->fs.nat_lip[5] << 16 |
				      f->fs.nat_lip[4] << 24, 1);

			set_tcb_field(adap, f, tid, TCB_SND_UNA_RAW_W + 3,
				      WORD_MASK, f->fs.nat_lip[3] |
				      f->fs.nat_lip[2] << 8 |
				      f->fs.nat_lip[1] << 16 |
				      f->fs.nat_lip[0] << 24, 1);
		} else {
			set_tcb_field(adap, f, tid, TCB_RX_FRAG3_LEN_RAW_W,
				      WORD_MASK, f->fs.nat_lip[3] |
				      f->fs.nat_lip[2] << 8 |
				      f->fs.nat_lip[1] << 16 |
				      f->fs.nat_lip[0] << 24, 1);
		}
	}

	if (sip) {
		if (f->fs.type) {
			set_tcb_field(adap, f, tid, TCB_RX_FRAG2_PTR_RAW_W,
				      WORD_MASK, f->fs.nat_fip[15] |
				      f->fs.nat_fip[14] << 8 |
				      f->fs.nat_fip[13] << 16 |
				      f->fs.nat_fip[12] << 24, 1);

			set_tcb_field(adap, f, tid, TCB_RX_FRAG2_PTR_RAW_W + 1,
				      WORD_MASK, f->fs.nat_fip[11] |
				      f->fs.nat_fip[10] << 8 |
				      f->fs.nat_fip[9] << 16 |
				      f->fs.nat_fip[8] << 24, 1);

			set_tcb_field(adap, f, tid, TCB_RX_FRAG2_PTR_RAW_W + 2,
				      WORD_MASK, f->fs.nat_fip[7] |
				      f->fs.nat_fip[6] << 8 |
				      f->fs.nat_fip[5] << 16 |
				      f->fs.nat_fip[4] << 24, 1);

			set_tcb_field(adap, f, tid, TCB_RX_FRAG2_PTR_RAW_W + 3,
				      WORD_MASK, f->fs.nat_fip[3] |
				      f->fs.nat_fip[2] << 8 |
				      f->fs.nat_fip[1] << 16 |
				      f->fs.nat_fip[0] << 24, 1);

		} else {
			set_tcb_field(adap, f, tid,
				      TCB_RX_FRAG3_START_IDX_OFFSET_RAW_W,
				      WORD_MASK, f->fs.nat_fip[3] |
				      f->fs.nat_fip[2] << 8 |
				      f->fs.nat_fip[1] << 16 |
				      f->fs.nat_fip[0] << 24, 1);
		}
	}

	set_tcb_field(adap, f, tid, TCB_PDU_HDR_LEN_W, WORD_MASK,
		      (dp ? f->fs.nat_lport : 0) |
		      (sp ? f->fs.nat_fport << 16 : 0), 1);
}