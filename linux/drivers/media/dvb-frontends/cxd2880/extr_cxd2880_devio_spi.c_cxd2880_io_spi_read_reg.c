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
struct cxd2880_spi {int (* write_read ) (struct cxd2880_spi*,int*,int,int*,int) ;} ;
struct cxd2880_io {struct cxd2880_spi* if_object; } ;
typedef  int /*<<< orphan*/  send_data ;
typedef  enum cxd2880_io_tgt { ____Placeholder_cxd2880_io_tgt } cxd2880_io_tgt ;

/* Variables and functions */
 int CXD2880_IO_TGT_SYS ; 
 int EINVAL ; 
 int stub1 (struct cxd2880_spi*,int*,int,int*,int) ; 

__attribute__((used)) static int cxd2880_io_spi_read_reg(struct cxd2880_io *io,
				   enum cxd2880_io_tgt tgt,
				   u8 sub_address, u8 *data,
				   u32 size)
{
	int ret = 0;
	struct cxd2880_spi *spi = NULL;
	u8 send_data[6];
	u8 *read_data_top = data;

	if (!io || !io->if_object || !data)
		return -EINVAL;

	if (sub_address + size > 0x100)
		return -EINVAL;

	spi = io->if_object;

	if (tgt == CXD2880_IO_TGT_SYS)
		send_data[0] = 0x0b;
	else
		send_data[0] = 0x0a;

	send_data[3] = 0;
	send_data[4] = 0;
	send_data[5] = 0;

	while (size > 0) {
		send_data[1] = sub_address;
		if (size > 255)
			send_data[2] = 255;
		else
			send_data[2] = size;

		ret =
		    spi->write_read(spi, send_data, sizeof(send_data),
				    read_data_top, send_data[2]);
		if (ret)
			return ret;

		sub_address += send_data[2];
		read_data_top += send_data[2];
		size -= send_data[2];
	}

	return ret;
}