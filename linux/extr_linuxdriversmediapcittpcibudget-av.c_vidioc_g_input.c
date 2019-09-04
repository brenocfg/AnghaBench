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
struct saa7146_fh {struct saa7146_dev* dev; } ;
struct saa7146_dev {scalar_t__ ext_priv; } ;
struct file {int dummy; } ;
struct budget_av {unsigned int cur_input; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (int,char*,unsigned int) ; 

__attribute__((used)) static int vidioc_g_input(struct file *file, void *fh, unsigned int *i)
{
	struct saa7146_dev *dev = ((struct saa7146_fh *)fh)->dev;
	struct budget_av *budget_av = (struct budget_av *)dev->ext_priv;

	*i = budget_av->cur_input;

	dprintk(1, "VIDIOC_G_INPUT %d\n", *i);
	return 0;
}