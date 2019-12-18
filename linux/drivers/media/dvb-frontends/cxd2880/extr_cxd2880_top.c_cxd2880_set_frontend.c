#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_9__ ;
typedef  struct TYPE_30__   TYPE_8__ ;
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_16__ ;
typedef  struct TYPE_21__   TYPE_14__ ;
typedef  struct TYPE_20__   TYPE_13__ ;
typedef  struct TYPE_19__   TYPE_12__ ;
typedef  struct TYPE_18__   TYPE_11__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct TYPE_19__ {int len; TYPE_11__* stat; } ;
struct TYPE_17__ {int len; TYPE_9__* stat; } ;
struct TYPE_30__ {int len; TYPE_7__* stat; } ;
struct TYPE_28__ {int len; TYPE_5__* stat; } ;
struct TYPE_26__ {int len; TYPE_3__* stat; } ;
struct TYPE_24__ {int len; TYPE_1__* stat; } ;
struct dtv_frontend_properties {int bandwidth_hz; scalar_t__ delivery_system; int frequency; scalar_t__ stream_id; TYPE_12__ block_count; TYPE_10__ block_error; TYPE_8__ post_bit_count; TYPE_6__ post_bit_error; TYPE_4__ pre_bit_count; TYPE_2__ pre_bit_error; } ;
struct dvb_frontend {struct dtv_frontend_properties dtv_property_cache; struct cxd2880_priv* demodulator_priv; } ;
struct TYPE_22__ {int center_freq_khz; int bandwidth; int /*<<< orphan*/  profile; scalar_t__ data_plp_id; } ;
struct TYPE_20__ {int /*<<< orphan*/  sys; } ;
struct TYPE_21__ {int center_freq_khz; int bandwidth; int /*<<< orphan*/  profile; } ;
struct cxd2880_priv {int /*<<< orphan*/  spi_mutex; TYPE_16__ dvbt2_tune_param; TYPE_13__ tnrdmd; TYPE_14__ dvbt_tune_param; scalar_t__ s; } ;
typedef  enum cxd2880_dtv_bandwidth { ____Placeholder_cxd2880_dtv_bandwidth } cxd2880_dtv_bandwidth ;
struct TYPE_31__ {scalar_t__ uvalue; void* scale; } ;
struct TYPE_29__ {scalar_t__ uvalue; void* scale; } ;
struct TYPE_27__ {scalar_t__ uvalue; void* scale; } ;
struct TYPE_25__ {scalar_t__ uvalue; void* scale; } ;
struct TYPE_23__ {scalar_t__ uvalue; void* scale; } ;
struct TYPE_18__ {scalar_t__ uvalue; void* scale; } ;

/* Variables and functions */
 int CXD2880_DTV_BW_1_7_MHZ ; 
 int CXD2880_DTV_BW_5_MHZ ; 
 int CXD2880_DTV_BW_6_MHZ ; 
 int CXD2880_DTV_BW_7_MHZ ; 
 int CXD2880_DTV_BW_8_MHZ ; 
 int /*<<< orphan*/  CXD2880_DTV_SYS_DVBT ; 
 int /*<<< orphan*/  CXD2880_DTV_SYS_DVBT2 ; 
 int /*<<< orphan*/  CXD2880_DVBT2_PROFILE_BASE ; 
 int /*<<< orphan*/  CXD2880_DVBT_PROFILE_HP ; 
 int EINVAL ; 
 void* FE_SCALE_NOT_AVAILABLE ; 
 scalar_t__ SYS_DVBT ; 
 scalar_t__ SYS_DVBT2 ; 
 int cxd2880_dvbt2_tune (TYPE_13__*,TYPE_16__*) ; 
 int cxd2880_dvbt_tune (TYPE_13__*,TYPE_14__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*,int,...) ; 

__attribute__((used)) static int cxd2880_set_frontend(struct dvb_frontend *fe)
{
	int ret;
	struct dtv_frontend_properties *c;
	struct cxd2880_priv *priv;
	enum cxd2880_dtv_bandwidth bw = CXD2880_DTV_BW_1_7_MHZ;

	if (!fe) {
		pr_err("invalid arg\n");
		return -EINVAL;
	}

	priv = fe->demodulator_priv;
	c = &fe->dtv_property_cache;

	c->pre_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->pre_bit_error.stat[0].uvalue = 0;
	c->pre_bit_error.len = 1;
	c->pre_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->pre_bit_count.stat[0].uvalue = 0;
	c->pre_bit_count.len = 1;
	c->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->post_bit_error.stat[0].uvalue = 0;
	c->post_bit_error.len = 1;
	c->post_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->post_bit_count.stat[0].uvalue = 0;
	c->post_bit_count.len = 1;
	c->block_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->block_error.stat[0].uvalue = 0;
	c->block_error.len = 1;
	c->block_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->block_count.stat[0].uvalue = 0;
	c->block_count.len = 1;

	switch (c->bandwidth_hz) {
	case 1712000:
		bw = CXD2880_DTV_BW_1_7_MHZ;
		break;
	case 5000000:
		bw = CXD2880_DTV_BW_5_MHZ;
		break;
	case 6000000:
		bw = CXD2880_DTV_BW_6_MHZ;
		break;
	case 7000000:
		bw = CXD2880_DTV_BW_7_MHZ;
		break;
	case 8000000:
		bw = CXD2880_DTV_BW_8_MHZ;
		break;
	default:
		return -EINVAL;
	}

	priv->s = 0;

	pr_info("sys:%d freq:%d bw:%d\n",
		c->delivery_system, c->frequency, bw);
	mutex_lock(priv->spi_mutex);
	if (c->delivery_system == SYS_DVBT) {
		priv->tnrdmd.sys = CXD2880_DTV_SYS_DVBT;
		priv->dvbt_tune_param.center_freq_khz = c->frequency / 1000;
		priv->dvbt_tune_param.bandwidth = bw;
		priv->dvbt_tune_param.profile = CXD2880_DVBT_PROFILE_HP;
		ret = cxd2880_dvbt_tune(&priv->tnrdmd,
					&priv->dvbt_tune_param);
	} else if (c->delivery_system == SYS_DVBT2) {
		priv->tnrdmd.sys = CXD2880_DTV_SYS_DVBT2;
		priv->dvbt2_tune_param.center_freq_khz = c->frequency / 1000;
		priv->dvbt2_tune_param.bandwidth = bw;
		priv->dvbt2_tune_param.data_plp_id = (u16)c->stream_id;
		priv->dvbt2_tune_param.profile = CXD2880_DVBT2_PROFILE_BASE;
		ret = cxd2880_dvbt2_tune(&priv->tnrdmd,
					 &priv->dvbt2_tune_param);
	} else {
		pr_err("invalid system\n");
		mutex_unlock(priv->spi_mutex);
		return -EINVAL;
	}
	mutex_unlock(priv->spi_mutex);

	pr_info("tune result %d\n", ret);

	return ret;
}