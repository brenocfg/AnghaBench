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
struct coda_dev {TYPE_1__* devtype; } ;
struct coda_codec {int src_fourcc; int dst_fourcc; } ;
struct TYPE_2__ {int num_codecs; struct coda_codec* codecs; } ;

/* Variables and functions */
 int coda_format_normalize_yuv (int) ; 

__attribute__((used)) static const struct coda_codec *coda_find_codec(struct coda_dev *dev,
						int src_fourcc, int dst_fourcc)
{
	const struct coda_codec *codecs = dev->devtype->codecs;
	int num_codecs = dev->devtype->num_codecs;
	int k;

	src_fourcc = coda_format_normalize_yuv(src_fourcc);
	dst_fourcc = coda_format_normalize_yuv(dst_fourcc);
	if (src_fourcc == dst_fourcc)
		return NULL;

	for (k = 0; k < num_codecs; k++) {
		if (codecs[k].src_fourcc == src_fourcc &&
		    codecs[k].dst_fourcc == dst_fourcc)
			break;
	}

	if (k == num_codecs)
		return NULL;

	return &codecs[k];
}