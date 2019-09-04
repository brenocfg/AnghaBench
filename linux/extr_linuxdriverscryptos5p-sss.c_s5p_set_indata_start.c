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
struct scatterlist {int dummy; } ;
struct s5p_aes_dev {struct scatterlist* sg_src_cpy; int /*<<< orphan*/  dev; } ;
struct ablkcipher_request {struct scatterlist* src; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  s5p_free_sg_cpy (struct s5p_aes_dev*,struct scatterlist**) ; 
 int /*<<< orphan*/  s5p_is_sg_aligned (struct scatterlist*) ; 
 int s5p_make_sg_cpy (struct s5p_aes_dev*,struct scatterlist*,struct scatterlist**) ; 
 int s5p_set_indata (struct s5p_aes_dev*,struct scatterlist*) ; 

__attribute__((used)) static int s5p_set_indata_start(struct s5p_aes_dev *dev,
				struct ablkcipher_request *req)
{
	struct scatterlist *sg;
	int err;

	dev->sg_src_cpy = NULL;
	sg = req->src;
	if (!s5p_is_sg_aligned(sg)) {
		dev_dbg(dev->dev,
			"At least one unaligned source scatter list, making a copy\n");
		err = s5p_make_sg_cpy(dev, sg, &dev->sg_src_cpy);
		if (err)
			return err;

		sg = dev->sg_src_cpy;
	}

	err = s5p_set_indata(dev, sg);
	if (err) {
		s5p_free_sg_cpy(dev, &dev->sg_src_cpy);
		return err;
	}

	return 0;
}