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
struct vm_area_struct {int dummy; } ;
struct scif_endpt {int dummy; } ;
struct file {struct scif_endpt* private_data; } ;

/* Variables and functions */
 int scif_mmap (struct vm_area_struct*,struct scif_endpt*) ; 

__attribute__((used)) static int scif_fdmmap(struct file *f, struct vm_area_struct *vma)
{
	struct scif_endpt *priv = f->private_data;

	return scif_mmap(vma, priv);
}