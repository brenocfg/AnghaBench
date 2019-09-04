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
struct si470x_device {int (* fops_release ) (struct file*) ;} ;
struct file {int dummy; } ;

/* Variables and functions */
 int stub1 (struct file*) ; 
 struct si470x_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int si470x_fops_release(struct file *file)
{
	struct si470x_device *radio = video_drvdata(file);

	return radio->fops_release(file);
}