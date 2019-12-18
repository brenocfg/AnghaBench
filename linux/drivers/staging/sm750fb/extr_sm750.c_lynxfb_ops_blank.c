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
struct lynxfb_output {int (* proc_setBLANK ) (struct lynxfb_output*,int) ;} ;
struct lynxfb_par {struct lynxfb_output output; } ;
struct fb_info {struct lynxfb_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int stub1 (struct lynxfb_output*,int) ; 

__attribute__((used)) static int lynxfb_ops_blank(int blank, struct fb_info *info)
{
	struct lynxfb_par *par;
	struct lynxfb_output *output;

	pr_debug("blank = %d.\n", blank);
	par = info->par;
	output = &par->output;
	return output->proc_setBLANK(output, blank);
}