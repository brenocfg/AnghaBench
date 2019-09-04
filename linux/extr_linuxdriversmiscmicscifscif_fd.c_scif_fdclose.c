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
struct scif_endpt {int dummy; } ;
struct inode {int dummy; } ;
struct file {struct scif_endpt* private_data; } ;

/* Variables and functions */
 int scif_close (struct scif_endpt*) ; 

__attribute__((used)) static int scif_fdclose(struct inode *inode, struct file *f)
{
	struct scif_endpt *priv = f->private_data;

	return scif_close(priv);
}