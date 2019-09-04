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
struct s5p_aes_dev {int /*<<< orphan*/  sg_src; } ;

/* Variables and functions */
 int s5p_set_indata (struct s5p_aes_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s5p_unset_indata (struct s5p_aes_dev*) ; 
 int /*<<< orphan*/  sg_is_last (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_next (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s5p_aes_rx(struct s5p_aes_dev *dev/*, bool *set_dma*/)
{
	int ret = 0;

	s5p_unset_indata(dev);

	if (!sg_is_last(dev->sg_src)) {
		ret = s5p_set_indata(dev, sg_next(dev->sg_src));
		if (!ret)
			ret = 1;
	}

	return ret;
}