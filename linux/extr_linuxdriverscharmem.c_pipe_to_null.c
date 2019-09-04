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
struct splice_desc {int len; } ;
struct pipe_inode_info {int dummy; } ;
struct pipe_buffer {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int pipe_to_null(struct pipe_inode_info *info, struct pipe_buffer *buf,
			struct splice_desc *sd)
{
	return sd->len;
}