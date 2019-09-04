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
typedef  int u8 ;
typedef  int u32 ;
struct cxd2880_spi {int (* write ) (struct cxd2880_spi*,int*,int) ;} ;
struct cxd2880_io {struct cxd2880_spi* if_object; } ;
typedef  enum cxd2880_io_tgt { ____Placeholder_cxd2880_io_tgt } cxd2880_io_tgt ;

/* Variables and functions */
 int BURST_WRITE_MAX ; 
 int CXD2880_IO_TGT_SYS ; 
 int EINVAL ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 
 int stub1 (struct cxd2880_spi*,int*,int) ; 
 int stub2 (struct cxd2880_spi*,int*,int) ; 

__attribute__((used)) static int cxd2880_io_spi_write_reg(struct cxd2880_io *io,
				    enum cxd2880_io_tgt tgt,
				    u8 sub_address,
				    const u8 *data, u32 size)
{
	int ret = 0;
	struct cxd2880_spi *spi = NULL;
	u8 send_data[BURST_WRITE_MAX + 4];
	const u8 *write_data_top = data;

	if (!io || !io->if_object || !data)
		return -EINVAL;

	if (size > BURST_WRITE_MAX)
		return -EINVAL;

	if (sub_address + size > 0x100)
		return -EINVAL;

	spi = io->if_object;

	if (tgt == CXD2880_IO_TGT_SYS)
		send_data[0] = 0x0f;
	else
		send_data[0] = 0x0e;

	while (size > 0) {
		send_data[1] = sub_address;
		if (size > 255)
			send_data[2] = 255;
		else
			send_data[2] = size;

		memcpy(&send_data[3], write_data_top, send_data[2]);

		if (tgt == CXD2880_IO_TGT_SYS) {
			send_data[3 + send_data[2]] = 0x00;
			ret = spi->write(spi, send_data, send_data[2] + 4);
		} else {
			ret = spi->write(spi, send_data, send_data[2] + 3);
		}
		if (ret)
			return ret;

		sub_address += send_data[2];
		write_data_top += send_data[2];
		size -= send_data[2];
	}

	return ret;
}