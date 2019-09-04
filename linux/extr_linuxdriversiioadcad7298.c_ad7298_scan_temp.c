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
typedef  int /*<<< orphan*/  u8 ;
struct ad7298_state {int ext_ref; int /*<<< orphan*/  spi; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int AD7298_TAVG ; 
 int AD7298_TSENSE ; 
 int AD7298_WRITE ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int sign_extend32 (int /*<<< orphan*/ ,int) ; 
 int spi_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int spi_write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int ad7298_scan_temp(struct ad7298_state *st, int *val)
{
	int ret;
	__be16 buf;

	buf = cpu_to_be16(AD7298_WRITE | AD7298_TSENSE |
			  AD7298_TAVG | st->ext_ref);

	ret = spi_write(st->spi, (u8 *)&buf, 2);
	if (ret)
		return ret;

	buf = cpu_to_be16(0);

	ret = spi_write(st->spi, (u8 *)&buf, 2);
	if (ret)
		return ret;

	usleep_range(101, 1000); /* sleep > 100us */

	ret = spi_read(st->spi, (u8 *)&buf, 2);
	if (ret)
		return ret;

	*val = sign_extend32(be16_to_cpu(buf), 11);

	return 0;
}