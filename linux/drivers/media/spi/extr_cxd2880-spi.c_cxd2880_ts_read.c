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
typedef  int u32 ;
struct cxd2880_ts_buf_info {int pkt_num; } ;
struct cxd2880_dvb_spi {int /*<<< orphan*/  ts_buf; int /*<<< orphan*/  demux; int /*<<< orphan*/  spi; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int EINVAL ; 
 int MAX_TRANS_PKT ; 
 int cxd2880_spi_clear_ts_buffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxd2880_spi_read_ts (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int cxd2880_spi_read_ts_buffer_info (int /*<<< orphan*/ ,struct cxd2880_ts_buf_info*) ; 
 int /*<<< orphan*/  dvb_dmx_swfilter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ktime_to_ms (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int cxd2880_ts_read(void *arg)
{
	struct cxd2880_dvb_spi *dvb_spi = NULL;
	struct cxd2880_ts_buf_info info;
	ktime_t start;
	u32 i;
	int ret;

	dvb_spi = arg;
	if (!dvb_spi) {
		pr_err("invalid arg\n");
		return -EINVAL;
	}

	ret = cxd2880_spi_clear_ts_buffer(dvb_spi->spi);
	if (ret) {
		pr_err("set_clear_ts_buffer failed\n");
		return ret;
	}

	start = ktime_get();
	while (!kthread_should_stop()) {
		ret = cxd2880_spi_read_ts_buffer_info(dvb_spi->spi,
						      &info);
		if (ret) {
			pr_err("spi_read_ts_buffer_info error\n");
			return ret;
		}

		if (info.pkt_num > MAX_TRANS_PKT) {
			for (i = 0; i < info.pkt_num / MAX_TRANS_PKT; i++) {
				cxd2880_spi_read_ts(dvb_spi->spi,
						    dvb_spi->ts_buf,
						    MAX_TRANS_PKT);
				dvb_dmx_swfilter(&dvb_spi->demux,
						 dvb_spi->ts_buf,
						 MAX_TRANS_PKT * 188);
			}
			start = ktime_get();
		} else if ((info.pkt_num > 0) &&
			   (ktime_to_ms(ktime_sub(ktime_get(), start)) >= 500)) {
			cxd2880_spi_read_ts(dvb_spi->spi,
					    dvb_spi->ts_buf,
					    info.pkt_num);
			dvb_dmx_swfilter(&dvb_spi->demux,
					 dvb_spi->ts_buf,
					 info.pkt_num * 188);
			start = ktime_get();
		} else {
			usleep_range(10000, 11000);
		}
	}

	return 0;
}