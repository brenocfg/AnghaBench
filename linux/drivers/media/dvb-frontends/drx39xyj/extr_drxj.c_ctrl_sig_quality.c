#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_9__ ;
typedef  struct TYPE_33__   TYPE_8__ ;
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_17__ ;
typedef  struct TYPE_24__   TYPE_16__ ;
typedef  struct TYPE_23__   TYPE_15__ ;
typedef  struct TYPE_22__   TYPE_14__ ;
typedef  struct TYPE_21__   TYPE_13__ ;
typedef  struct TYPE_20__   TYPE_12__ ;
typedef  struct TYPE_19__   TYPE_11__ ;
typedef  struct TYPE_18__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  unsigned long u16 ;
struct i2c_device_addr {struct drx39xxj_state* user_data; } ;
struct TYPE_32__ {TYPE_6__* stat; } ;
struct TYPE_30__ {TYPE_4__* stat; } ;
struct TYPE_24__ {TYPE_17__* stat; } ;
struct TYPE_23__ {TYPE_14__* stat; } ;
struct TYPE_21__ {TYPE_12__* stat; } ;
struct TYPE_19__ {TYPE_10__* stat; } ;
struct TYPE_34__ {TYPE_8__* stat; } ;
struct TYPE_28__ {TYPE_2__* stat; } ;
struct dtv_frontend_properties {TYPE_7__ cnr; TYPE_5__ post_bit_count; TYPE_16__ post_bit_error; TYPE_15__ pre_bit_count; TYPE_13__ pre_bit_error; TYPE_11__ block_count; TYPE_9__ block_error; TYPE_3__ strength; } ;
struct drxj_data {int standard; } ;
struct drx_demod_instance {struct drxj_data* my_ext_attr; struct i2c_device_addr* my_i2c_dev_addr; } ;
struct TYPE_26__ {struct dtv_frontend_properties dtv_property_cache; } ;
struct drx39xxj_state {TYPE_1__ frontend; } ;
typedef  enum drx_standard { ____Placeholder_drx_standard } drx_standard ;
typedef  enum drx_lock_status { ____Placeholder_drx_lock_status } drx_lock_status ;
struct TYPE_33__ {int /*<<< orphan*/  uvalue; void* scale; } ;
struct TYPE_31__ {unsigned long svalue; void* scale; } ;
struct TYPE_29__ {int /*<<< orphan*/  uvalue; void* scale; } ;
struct TYPE_27__ {unsigned long uvalue; void* scale; } ;
struct TYPE_25__ {int /*<<< orphan*/  uvalue; void* scale; } ;
struct TYPE_22__ {int /*<<< orphan*/  uvalue; void* scale; } ;
struct TYPE_20__ {int /*<<< orphan*/  uvalue; void* scale; } ;
struct TYPE_18__ {int /*<<< orphan*/  uvalue; void* scale; } ;

/* Variables and functions */
 int DRXJ_DEMOD_LOCK ; 
 int DRX_LOCKED ; 
#define  DRX_STANDARD_8VSB 131 
#define  DRX_STANDARD_ITU_A 130 
#define  DRX_STANDARD_ITU_B 129 
#define  DRX_STANDARD_ITU_C 128 
 int EIO ; 
 void* FE_SCALE_COUNTER ; 
 void* FE_SCALE_DECIBEL ; 
 void* FE_SCALE_NOT_AVAILABLE ; 
 void* FE_SCALE_RELATIVE ; 
 int ctrl_get_qam_sig_quality (struct drx_demod_instance*) ; 
 int get_acc_pkt_err (struct drx_demod_instance*,int /*<<< orphan*/ *) ; 
 int get_sig_strength (struct drx_demod_instance*,unsigned long*) ; 
 int get_vs_bpost_viterbi_ber (struct i2c_device_addr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int get_vs_bpre_viterbi_ber (struct i2c_device_addr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int get_vsb_post_rs_pck_err (struct i2c_device_addr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int get_vsbmer (struct i2c_device_addr*,unsigned long*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static int
ctrl_sig_quality(struct drx_demod_instance *demod,
		 enum drx_lock_status lock_status)
{
	struct i2c_device_addr *dev_addr = demod->my_i2c_dev_addr;
	struct drxj_data *ext_attr = demod->my_ext_attr;
	struct drx39xxj_state *state = dev_addr->user_data;
	struct dtv_frontend_properties *p = &state->frontend.dtv_property_cache;
	enum drx_standard standard = ext_attr->standard;
	int rc;
	u32 ber, cnt, err, pkt;
	u16 mer, strength = 0;

	rc = get_sig_strength(demod, &strength);
	if (rc < 0) {
		pr_err("error getting signal strength %d\n", rc);
		p->strength.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	} else {
		p->strength.stat[0].scale = FE_SCALE_RELATIVE;
		p->strength.stat[0].uvalue = 65535UL *  strength/ 100;
	}

	switch (standard) {
	case DRX_STANDARD_8VSB:
#ifdef DRXJ_SIGNAL_ACCUM_ERR
		rc = get_acc_pkt_err(demod, &pkt);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
#endif
		if (lock_status != DRXJ_DEMOD_LOCK && lock_status != DRX_LOCKED) {
			p->pre_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
			p->pre_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
			p->post_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
			p->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
			p->block_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
			p->block_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
			p->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		} else {
			rc = get_vsb_post_rs_pck_err(dev_addr, &err, &pkt);
			if (rc != 0) {
				pr_err("error %d getting UCB\n", rc);
				p->block_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
			} else {
				p->block_error.stat[0].scale = FE_SCALE_COUNTER;
				p->block_error.stat[0].uvalue += err;
				p->block_count.stat[0].scale = FE_SCALE_COUNTER;
				p->block_count.stat[0].uvalue += pkt;
			}

			/* PostViterbi is compute in steps of 10^(-6) */
			rc = get_vs_bpre_viterbi_ber(dev_addr, &ber, &cnt);
			if (rc != 0) {
				pr_err("error %d getting pre-ber\n", rc);
				p->pre_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
			} else {
				p->pre_bit_error.stat[0].scale = FE_SCALE_COUNTER;
				p->pre_bit_error.stat[0].uvalue += ber;
				p->pre_bit_count.stat[0].scale = FE_SCALE_COUNTER;
				p->pre_bit_count.stat[0].uvalue += cnt;
			}

			rc = get_vs_bpost_viterbi_ber(dev_addr, &ber, &cnt);
			if (rc != 0) {
				pr_err("error %d getting post-ber\n", rc);
				p->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
			} else {
				p->post_bit_error.stat[0].scale = FE_SCALE_COUNTER;
				p->post_bit_error.stat[0].uvalue += ber;
				p->post_bit_count.stat[0].scale = FE_SCALE_COUNTER;
				p->post_bit_count.stat[0].uvalue += cnt;
			}
			rc = get_vsbmer(dev_addr, &mer);
			if (rc != 0) {
				pr_err("error %d getting MER\n", rc);
				p->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
			} else {
				p->cnr.stat[0].svalue = mer * 100;
				p->cnr.stat[0].scale = FE_SCALE_DECIBEL;
			}
		}
		break;
#ifndef DRXJ_VSB_ONLY
	case DRX_STANDARD_ITU_A:
	case DRX_STANDARD_ITU_B:
	case DRX_STANDARD_ITU_C:
		rc = ctrl_get_qam_sig_quality(demod);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		break;
#endif
	default:
		return -EIO;
	}

	return 0;
rw_error:
	return rc;
}