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
struct imgu_device {int dummy; } ;
struct imgu_css_pipe {TYPE_1__* aux_frames; int /*<<< orphan*/ ** binary_params_cs; } ;
struct imgu_css {struct imgu_css_pipe* pipes; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * mem; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSS_ABI_SIZE ; 
 int /*<<< orphan*/  CSS_BDS_SIZE ; 
 int /*<<< orphan*/  CSS_GDC_SIZE ; 
 int ENOMEM ; 
 unsigned int IMGU_ABI_NUM_MEMORIES ; 
 unsigned int IMGU_ABI_PARAM_CLASS_CONFIG ; 
 unsigned int IMGU_ABI_PARAM_CLASS_NUM ; 
 unsigned int IPU3_CSS_AUX_FRAMES ; 
 size_t IPU3_CSS_AUX_FRAME_REF ; 
 size_t IPU3_CSS_AUX_FRAME_TNR ; 
 struct imgu_device* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imgu_css_binary_cleanup (struct imgu_css*,unsigned int) ; 
 int /*<<< orphan*/  imgu_dmamap_alloc (struct imgu_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int imgu_css_binary_preallocate(struct imgu_css *css, unsigned int pipe)
{
	struct imgu_device *imgu = dev_get_drvdata(css->dev);
	unsigned int i, j;

	struct imgu_css_pipe *css_pipe = &css->pipes[pipe];

	for (j = IMGU_ABI_PARAM_CLASS_CONFIG;
	     j < IMGU_ABI_PARAM_CLASS_NUM; j++)
		for (i = 0; i < IMGU_ABI_NUM_MEMORIES; i++)
			if (!imgu_dmamap_alloc(imgu,
					       &css_pipe->binary_params_cs[j - 1][i],
					       CSS_ABI_SIZE))
				goto out_of_memory;

	for (i = 0; i < IPU3_CSS_AUX_FRAMES; i++)
		if (!imgu_dmamap_alloc(imgu,
				       &css_pipe->aux_frames[IPU3_CSS_AUX_FRAME_REF].
				       mem[i], CSS_BDS_SIZE))
			goto out_of_memory;

	for (i = 0; i < IPU3_CSS_AUX_FRAMES; i++)
		if (!imgu_dmamap_alloc(imgu,
				       &css_pipe->aux_frames[IPU3_CSS_AUX_FRAME_TNR].
				       mem[i], CSS_GDC_SIZE))
			goto out_of_memory;

	return 0;

out_of_memory:
	imgu_css_binary_cleanup(css, pipe);
	return -ENOMEM;
}