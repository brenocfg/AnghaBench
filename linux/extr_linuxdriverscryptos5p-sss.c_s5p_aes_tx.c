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
struct s5p_aes_dev {int /*<<< orphan*/  sg_dst; } ;

/* Variables and functions */
 int s5p_set_outdata (struct s5p_aes_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s5p_unset_outdata (struct s5p_aes_dev*) ; 
 int /*<<< orphan*/  sg_is_last (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_next (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s5p_aes_tx(struct s5p_aes_dev *dev)
{
	int ret = 0;

	s5p_unset_outdata(dev);

	if (!sg_is_last(dev->sg_dst)) {
		ret = s5p_set_outdata(dev, sg_next(dev->sg_dst));
		if (!ret)
			ret = 1;
	}

	return ret;
}