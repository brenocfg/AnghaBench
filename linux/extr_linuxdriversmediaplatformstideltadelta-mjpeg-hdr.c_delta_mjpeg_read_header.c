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
struct mjpeg_header {int dummy; } ;
struct delta_dev {int /*<<< orphan*/  dev; } ;
struct delta_ctx {int /*<<< orphan*/  name; struct delta_dev* dev; } ;
typedef  int /*<<< orphan*/  str ;

/* Variables and functions */
 int EINVAL ; 
 int ENODATA ; 
 unsigned char MJPEG_MARKER ; 
#define  MJPEG_SOF_0 130 
#define  MJPEG_SOF_1 129 
#define  MJPEG_SOI 128 
 unsigned int delta_mjpeg_read_sof (struct delta_ctx*,unsigned char*,unsigned int,struct mjpeg_header*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  header_str (struct mjpeg_header*,unsigned char*,int) ; 

int delta_mjpeg_read_header(struct delta_ctx *pctx,
			    unsigned char *data, unsigned int size,
			    struct mjpeg_header *header,
			    unsigned int *data_offset)
{
	struct delta_dev *delta = pctx->dev;
	unsigned char str[200];

	unsigned int ret = 0;
	unsigned int offset = 0;
	unsigned int soi = 0;

	if (size < 2)
		goto err_no_more;

	offset = 0;
	while (1) {
		if (data[offset] == MJPEG_MARKER)
			switch (data[offset + 1]) {
			case MJPEG_SOI:
				soi = 1;
				*data_offset = offset;
				break;

			case MJPEG_SOF_0:
			case MJPEG_SOF_1:
				if (!soi) {
					dev_err(delta->dev,
						"%s   wrong sequence, got SOF while SOI not seen\n",
						pctx->name);
					return -EINVAL;
				}

				ret = delta_mjpeg_read_sof(pctx,
							   &data[offset + 2],
							   size - (offset + 2),
							   header);
				if (ret)
					goto err;

				goto done;

			default:
				break;
			}

		offset++;
		if ((offset + 2) >= size)
			goto err_no_more;
	}

done:
	dev_dbg(delta->dev,
		"%s   found header @ offset %d:\n%s", pctx->name,
		*data_offset,
		header_str(header, str, sizeof(str)));
	return 0;

err_no_more:
	dev_err(delta->dev,
		"%s   no header found within %d bytes input stream\n",
		pctx->name, size);
	return -ENODATA;

err:
	return ret;
}