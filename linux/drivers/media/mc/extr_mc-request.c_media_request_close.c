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
struct media_request {int dummy; } ;
struct inode {int dummy; } ;
struct file {struct media_request* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  media_request_put (struct media_request*) ; 

__attribute__((used)) static int media_request_close(struct inode *inode, struct file *filp)
{
	struct media_request *req = filp->private_data;

	media_request_put(req);
	return 0;
}