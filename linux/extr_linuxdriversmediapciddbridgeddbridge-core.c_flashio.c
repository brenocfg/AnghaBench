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
typedef  size_t u8 ;
typedef  size_t u32 ;
struct ddb_link {int /*<<< orphan*/  flash_mutex; } ;
struct ddb {struct ddb_link* link; } ;

/* Variables and functions */
 size_t DDB_LINK_TAG (size_t) ; 
 size_t SPI_CONTROL ; 
 size_t SPI_DATA ; 
 size_t ddbreadl (struct ddb*,size_t) ; 
 int /*<<< orphan*/  ddbwritel (struct ddb*,int,size_t) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ reg_wait (struct ddb*,size_t,int) ; 
 size_t swab32 (size_t) ; 

__attribute__((used)) static int flashio(struct ddb *dev, u32 lnr, u8 *wbuf, u32 wlen, u8 *rbuf,
		   u32 rlen)
{
	u32 data, shift;
	u32 tag = DDB_LINK_TAG(lnr);
	struct ddb_link *link = &dev->link[lnr];

	mutex_lock(&link->flash_mutex);
	if (wlen > 4)
		ddbwritel(dev, 1, tag | SPI_CONTROL);
	while (wlen > 4) {
		/* FIXME: check for big-endian */
		data = swab32(*(u32 *)wbuf);
		wbuf += 4;
		wlen -= 4;
		ddbwritel(dev, data, tag | SPI_DATA);
		if (reg_wait(dev, tag | SPI_CONTROL, 4))
			goto fail;
	}
	if (rlen)
		ddbwritel(dev, 0x0001 | ((wlen << (8 + 3)) & 0x1f00),
			  tag | SPI_CONTROL);
	else
		ddbwritel(dev, 0x0003 | ((wlen << (8 + 3)) & 0x1f00),
			  tag | SPI_CONTROL);

	data = 0;
	shift = ((4 - wlen) * 8);
	while (wlen) {
		data <<= 8;
		data |= *wbuf;
		wlen--;
		wbuf++;
	}
	if (shift)
		data <<= shift;
	ddbwritel(dev, data, tag | SPI_DATA);
	if (reg_wait(dev, tag | SPI_CONTROL, 4))
		goto fail;

	if (!rlen) {
		ddbwritel(dev, 0, tag | SPI_CONTROL);
		goto exit;
	}
	if (rlen > 4)
		ddbwritel(dev, 1, tag | SPI_CONTROL);

	while (rlen > 4) {
		ddbwritel(dev, 0xffffffff, tag | SPI_DATA);
		if (reg_wait(dev, tag | SPI_CONTROL, 4))
			goto fail;
		data = ddbreadl(dev, tag | SPI_DATA);
		*(u32 *)rbuf = swab32(data);
		rbuf += 4;
		rlen -= 4;
	}
	ddbwritel(dev, 0x0003 | ((rlen << (8 + 3)) & 0x1F00),
		  tag | SPI_CONTROL);
	ddbwritel(dev, 0xffffffff, tag | SPI_DATA);
	if (reg_wait(dev, tag | SPI_CONTROL, 4))
		goto fail;

	data = ddbreadl(dev, tag | SPI_DATA);
	ddbwritel(dev, 0, tag | SPI_CONTROL);

	if (rlen < 4)
		data <<= ((4 - rlen) * 8);

	while (rlen > 0) {
		*rbuf = ((data >> 24) & 0xff);
		data <<= 8;
		rbuf++;
		rlen--;
	}
exit:
	mutex_unlock(&link->flash_mutex);
	return 0;
fail:
	mutex_unlock(&link->flash_mutex);
	return -1;
}