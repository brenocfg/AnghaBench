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
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DST_CA_DEBUG ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,struct file*) ; 
 int /*<<< orphan*/  verbose ; 

__attribute__((used)) static int dst_ca_open(struct inode *inode, struct file *file)
{
	dprintk(verbose, DST_CA_DEBUG, 1, " Device opened [%p] ", file);

	return 0;
}