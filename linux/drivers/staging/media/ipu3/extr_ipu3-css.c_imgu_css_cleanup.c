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
struct imgu_device {int dummy; } ;
struct imgu_css {int /*<<< orphan*/  xmem_sp_group_ptrs; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int IMGU_MAX_PIPE_NUM ; 
 struct imgu_device* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imgu_css_fw_cleanup (struct imgu_css*) ; 
 int /*<<< orphan*/  imgu_css_pipe_cleanup (struct imgu_css*,unsigned int) ; 
 int /*<<< orphan*/  imgu_css_stop_streaming (struct imgu_css*) ; 
 int /*<<< orphan*/  imgu_dmamap_free (struct imgu_device*,int /*<<< orphan*/ *) ; 

void imgu_css_cleanup(struct imgu_css *css)
{
	struct imgu_device *imgu = dev_get_drvdata(css->dev);
	unsigned int pipe;

	imgu_css_stop_streaming(css);
	for (pipe = 0; pipe < IMGU_MAX_PIPE_NUM; pipe++)
		imgu_css_pipe_cleanup(css, pipe);
	imgu_dmamap_free(imgu, &css->xmem_sp_group_ptrs);
	imgu_css_fw_cleanup(css);
}