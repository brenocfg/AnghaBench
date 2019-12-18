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
struct scsi_pointer {int /*<<< orphan*/  buffers_residual; int /*<<< orphan*/  buffer; int /*<<< orphan*/  this_residual; int /*<<< orphan*/  ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  printk (char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void print_SCp(struct scsi_pointer *SCp, const char *prefix, const char *suffix)
{
	printk("%sptr %p this_residual 0x%x buffer %p buffers_residual 0x%x%s",
		prefix, SCp->ptr, SCp->this_residual, SCp->buffer,
		SCp->buffers_residual, suffix);
}