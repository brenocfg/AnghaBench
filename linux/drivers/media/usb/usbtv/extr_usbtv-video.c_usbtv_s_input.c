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
struct usbtv {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int usbtv_select_input (struct usbtv*,unsigned int) ; 
 struct usbtv* video_drvdata (struct file*) ; 

__attribute__((used)) static int usbtv_s_input(struct file *file, void *priv, unsigned int i)
{
	struct usbtv *usbtv = video_drvdata(file);

	return usbtv_select_input(usbtv, i);
}