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
struct ifreq {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 long __tun_chr_ioctl (struct file*,unsigned int,unsigned long,int) ; 

__attribute__((used)) static long tun_chr_ioctl(struct file *file,
			  unsigned int cmd, unsigned long arg)
{
	return __tun_chr_ioctl(file, cmd, arg, sizeof (struct ifreq));
}