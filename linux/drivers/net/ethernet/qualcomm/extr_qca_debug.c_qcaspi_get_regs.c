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
typedef  size_t u32 ;
typedef  size_t u16 ;
struct qcaspi {int dummy; } ;
struct net_device {int dummy; } ;
struct ethtool_regs {int version; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int*) ; 
 int QCASPI_MAX_REGS ; 
 int /*<<< orphan*/  memset (size_t*,int /*<<< orphan*/ ,int) ; 
 struct qcaspi* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  qcaspi_read_register (struct qcaspi*,int,size_t*) ; 
 int* qcaspi_spi_regs ; 

__attribute__((used)) static void
qcaspi_get_regs(struct net_device *dev, struct ethtool_regs *regs, void *p)
{
	struct qcaspi *qca = netdev_priv(dev);
	u32 *regs_buff = p;
	unsigned int i;

	regs->version = 1;
	memset(regs_buff, 0, sizeof(u32) * QCASPI_MAX_REGS);

	for (i = 0; i < ARRAY_SIZE(qcaspi_spi_regs); i++) {
		u16 offset, value;

		qcaspi_read_register(qca, qcaspi_spi_regs[i], &value);
		offset = qcaspi_spi_regs[i] >> 8;
		regs_buff[offset] = value;
	}
}