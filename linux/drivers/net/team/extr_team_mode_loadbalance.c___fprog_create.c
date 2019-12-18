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
typedef  int u32 ;
struct sock_fprog_kern {int len; int /*<<< orphan*/  filter; } ;
struct sock_filter {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct sock_fprog_kern*) ; 
 struct sock_fprog_kern* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmemdup (struct sock_filter*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __fprog_create(struct sock_fprog_kern **pfprog, u32 data_len,
			  const void *data)
{
	struct sock_fprog_kern *fprog;
	struct sock_filter *filter = (struct sock_filter *) data;

	if (data_len % sizeof(struct sock_filter))
		return -EINVAL;
	fprog = kmalloc(sizeof(*fprog), GFP_KERNEL);
	if (!fprog)
		return -ENOMEM;
	fprog->filter = kmemdup(filter, data_len, GFP_KERNEL);
	if (!fprog->filter) {
		kfree(fprog);
		return -ENOMEM;
	}
	fprog->len = data_len / sizeof(struct sock_filter);
	*pfprog = fprog;
	return 0;
}