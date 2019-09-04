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
struct s5p_aes_dev {scalar_t__ sg_dst_cpy; scalar_t__ sg_src_cpy; TYPE_1__* req; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  nbytes; int /*<<< orphan*/  dst; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s5p_free_sg_cpy (struct s5p_aes_dev*,scalar_t__*) ; 
 int /*<<< orphan*/  s5p_sg_copy_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sg_virt (scalar_t__) ; 

__attribute__((used)) static void s5p_sg_done(struct s5p_aes_dev *dev)
{
	if (dev->sg_dst_cpy) {
		dev_dbg(dev->dev,
			"Copying %d bytes of output data back to original place\n",
			dev->req->nbytes);
		s5p_sg_copy_buf(sg_virt(dev->sg_dst_cpy), dev->req->dst,
				dev->req->nbytes, 1);
	}
	s5p_free_sg_cpy(dev, &dev->sg_src_cpy);
	s5p_free_sg_cpy(dev, &dev->sg_dst_cpy);
}