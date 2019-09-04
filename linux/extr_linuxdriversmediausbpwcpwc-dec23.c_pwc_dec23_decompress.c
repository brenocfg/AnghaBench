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
struct pwc_dec23_private {int /*<<< orphan*/  lock; } ;
struct pwc_device {int height; int width; int /*<<< orphan*/  vbandlength; struct pwc_dec23_private dec23; } ;

/* Variables and functions */
 int /*<<< orphan*/  DecompressBand23 (struct pwc_dec23_private*,void const*,unsigned char*,unsigned char*,unsigned char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void pwc_dec23_decompress(struct pwc_device *pdev,
			  const void *src,
			  void *dst)
{
	int bandlines_left, bytes_per_block;
	struct pwc_dec23_private *pdec = &pdev->dec23;

	/* YUV420P image format */
	unsigned char *pout_planar_y;
	unsigned char *pout_planar_u;
	unsigned char *pout_planar_v;
	unsigned int   plane_size;

	mutex_lock(&pdec->lock);

	bandlines_left = pdev->height / 4;
	bytes_per_block = pdev->width * 4;
	plane_size = pdev->height * pdev->width;

	pout_planar_y = dst;
	pout_planar_u = dst + plane_size;
	pout_planar_v = dst + plane_size + plane_size / 4;

	while (bandlines_left--) {
		DecompressBand23(pdec, src,
				 pout_planar_y, pout_planar_u, pout_planar_v,
				 pdev->width, pdev->width);
		src += pdev->vbandlength;
		pout_planar_y += bytes_per_block;
		pout_planar_u += pdev->width;
		pout_planar_v += pdev->width;
	}
	mutex_unlock(&pdec->lock);
}