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
struct device {int dummy; } ;

/* Variables and functions */
 int DPAA_GENALLOC_OFF ; 
 int ENODEV ; 
 int QM_FQID_RANGE_START ; 
 int /*<<< orphan*/  QM_SDQCR_CHANNELS_POOL_CONV (int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int gen_pool_add (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  qm_cgralloc ; 
 int qm_channel_pool1 ; 
 int /*<<< orphan*/  qm_fqalloc ; 
 int qm_get_fqid_maxcnt () ; 
 int /*<<< orphan*/  qm_pools_sdqcr ; 
 int /*<<< orphan*/  qm_qpalloc ; 
 int qman_ip_rev ; 

__attribute__((used)) static int qman_resource_init(struct device *dev)
{
	int pool_chan_num, cgrid_num;
	int ret, i;

	switch (qman_ip_rev >> 8) {
	case 1:
		pool_chan_num = 15;
		cgrid_num = 256;
		break;
	case 2:
		pool_chan_num = 3;
		cgrid_num = 64;
		break;
	case 3:
		pool_chan_num = 15;
		cgrid_num = 256;
		break;
	default:
		return -ENODEV;
	}

	ret = gen_pool_add(qm_qpalloc, qm_channel_pool1 | DPAA_GENALLOC_OFF,
			   pool_chan_num, -1);
	if (ret) {
		dev_err(dev, "Failed to seed pool channels (%d)\n", ret);
		return ret;
	}

	ret = gen_pool_add(qm_cgralloc, DPAA_GENALLOC_OFF, cgrid_num, -1);
	if (ret) {
		dev_err(dev, "Failed to seed CGRID range (%d)\n", ret);
		return ret;
	}

	/* parse pool channels into the SDQCR mask */
	for (i = 0; i < cgrid_num; i++)
		qm_pools_sdqcr |= QM_SDQCR_CHANNELS_POOL_CONV(i);

	ret = gen_pool_add(qm_fqalloc, QM_FQID_RANGE_START | DPAA_GENALLOC_OFF,
			   qm_get_fqid_maxcnt() - QM_FQID_RANGE_START, -1);
	if (ret) {
		dev_err(dev, "Failed to seed FQID range (%d)\n", ret);
		return ret;
	}

	return 0;
}