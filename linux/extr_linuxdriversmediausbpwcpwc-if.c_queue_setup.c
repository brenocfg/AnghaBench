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
struct vb2_queue {int dummy; } ;
struct pwc_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 unsigned int MAX_FRAMES ; 
 int /*<<< orphan*/  MAX_HEIGHT ; 
 int /*<<< orphan*/  MAX_WIDTH ; 
 unsigned int MIN_FRAMES ; 
 unsigned int PAGE_ALIGN (int) ; 
 int pwc_get_size (struct pwc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int** pwc_image_sizes ; 
 struct pwc_device* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static int queue_setup(struct vb2_queue *vq,
				unsigned int *nbuffers, unsigned int *nplanes,
				unsigned int sizes[], struct device *alloc_devs[])
{
	struct pwc_device *pdev = vb2_get_drv_priv(vq);
	int size;

	if (*nbuffers < MIN_FRAMES)
		*nbuffers = MIN_FRAMES;
	else if (*nbuffers > MAX_FRAMES)
		*nbuffers = MAX_FRAMES;

	*nplanes = 1;

	size = pwc_get_size(pdev, MAX_WIDTH, MAX_HEIGHT);
	sizes[0] = PAGE_ALIGN(pwc_image_sizes[size][0] *
			      pwc_image_sizes[size][1] * 3 / 2);

	return 0;
}