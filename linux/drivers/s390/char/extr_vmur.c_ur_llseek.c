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
struct file {int f_flags; } ;
typedef  int loff_t ;

/* Variables and functions */
 int ESPIPE ; 
 int O_ACCMODE ; 
 int O_RDONLY ; 
 int PAGE_SIZE ; 
 int no_seek_end_llseek (struct file*,int,int) ; 

__attribute__((used)) static loff_t ur_llseek(struct file *file, loff_t offset, int whence)
{
	if ((file->f_flags & O_ACCMODE) != O_RDONLY)
		return -ESPIPE; /* seek allowed only for reader */
	if (offset % PAGE_SIZE)
		return -ESPIPE; /* only multiples of 4K allowed */
	return no_seek_end_llseek(file, offset, whence);
}