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
typedef  int u8 ;
typedef  int u16 ;
struct spi_device {int dummy; } ;
struct cxd2880_pid_filter_config {TYPE_1__* pid_config; scalar_t__ is_negative; } ;
struct TYPE_2__ {int pid; scalar_t__ is_enable; } ;

/* Variables and functions */
 int CXD2880_MAX_FILTER_SIZE ; 
 int EINVAL ; 
 int cxd2880_write_reg (struct spi_device*,int,int*,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int cxd2880_set_pid_filter(struct spi_device *spi,
				  struct cxd2880_pid_filter_config *cfg)
{
	u8 data[65];
	int i;
	u16 pid = 0;
	int ret;

	if (!spi) {
		pr_err("invalid arg\n");
		return -EINVAL;
	}

	data[0] = 0x00;
	ret = cxd2880_write_reg(spi, 0x00, &data[0], 1);
	if (ret)
		return ret;
	if (!cfg) {
		data[0] = 0x02;
		ret = cxd2880_write_reg(spi, 0x50, &data[0], 1);
	} else {
		data[0] = cfg->is_negative ? 0x01 : 0x00;

		for (i = 0; i < CXD2880_MAX_FILTER_SIZE; i++) {
			pid = cfg->pid_config[i].pid;
			if (cfg->pid_config[i].is_enable) {
				data[1 + (i * 2)] = (pid >> 8) | 0x20;
				data[2 + (i * 2)] = pid & 0xff;
			} else {
				data[1 + (i * 2)] = 0x00;
				data[2 + (i * 2)] = 0x00;
			}
		}
		ret = cxd2880_write_reg(spi, 0x50, data, 65);
	}

	return ret;
}