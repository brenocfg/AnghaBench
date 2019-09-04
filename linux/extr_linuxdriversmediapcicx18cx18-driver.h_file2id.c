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
struct file {int /*<<< orphan*/  private_data; } ;
struct cx18_open_id {int dummy; } ;

/* Variables and functions */
 struct cx18_open_id* fh2id (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct cx18_open_id *file2id(struct file *file)
{
	return fh2id(file->private_data);
}