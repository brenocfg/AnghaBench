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
typedef  int /*<<< orphan*/  u_char ;
struct spi_nor {struct cqspi_flash_pdata* priv; } ;
struct cqspi_st {scalar_t__ ahb_base; } ;
struct cqspi_flash_pdata {scalar_t__ use_direct_mode; struct cqspi_st* cqspi; } ;
typedef  int ssize_t ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int cqspi_indirect_write_execute (struct spi_nor*,scalar_t__,int /*<<< orphan*/  const*,size_t) ; 
 int cqspi_set_protocol (struct spi_nor*,int /*<<< orphan*/ ) ; 
 int cqspi_wait_idle (struct cqspi_st*) ; 
 int cqspi_write_setup (struct spi_nor*) ; 
 int /*<<< orphan*/  memcpy_toio (scalar_t__,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static ssize_t cqspi_write(struct spi_nor *nor, loff_t to,
			   size_t len, const u_char *buf)
{
	struct cqspi_flash_pdata *f_pdata = nor->priv;
	struct cqspi_st *cqspi = f_pdata->cqspi;
	int ret;

	ret = cqspi_set_protocol(nor, 0);
	if (ret)
		return ret;

	ret = cqspi_write_setup(nor);
	if (ret)
		return ret;

	if (f_pdata->use_direct_mode) {
		memcpy_toio(cqspi->ahb_base + to, buf, len);
		ret = cqspi_wait_idle(cqspi);
	} else {
		ret = cqspi_indirect_write_execute(nor, to, buf, len);
	}
	if (ret)
		return ret;

	return len;
}