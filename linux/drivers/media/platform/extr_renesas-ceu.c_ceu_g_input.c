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
struct file {int dummy; } ;
struct ceu_device {unsigned int sd_index; } ;

/* Variables and functions */
 struct ceu_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int ceu_g_input(struct file *file, void *priv, unsigned int *i)
{
	struct ceu_device *ceudev = video_drvdata(file);

	*i = ceudev->sd_index;

	return 0;
}