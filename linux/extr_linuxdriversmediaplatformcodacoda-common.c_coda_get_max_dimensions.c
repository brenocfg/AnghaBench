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
struct coda_codec {unsigned int max_w; unsigned int max_h; } ;
struct TYPE_2__ {int num_codecs; struct coda_codec* codecs; } ;

/* Variables and functions */
 unsigned int max (unsigned int,unsigned int) ; 

__attribute__((used)) static void coda_get_max_dimensions(struct coda_dev *dev,
				    const struct coda_codec *codec,
				    int *max_w, int *max_h)
{
	const struct coda_codec *codecs = dev->devtype->codecs;
	int num_codecs = dev->devtype->num_codecs;
	unsigned int w, h;
	int k;

	if (codec) {
		w = codec->max_w;
		h = codec->max_h;
	} else {
		for (k = 0, w = 0, h = 0; k < num_codecs; k++) {
			w = max(w, codecs[k].max_w);
			h = max(h, codecs[k].max_h);
		}
	}

	if (max_w)
		*max_w = w;
	if (max_h)
		*max_h = h;
}