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
struct ctlr_info {int dummy; } ;
struct CommandList {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_REPLY_QUEUE ; 
 int /*<<< orphan*/  __enqueue_cmd_and_start_io (struct ctlr_info*,struct CommandList*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void enqueue_cmd_and_start_io(struct ctlr_info *h, struct CommandList *c)
{
	__enqueue_cmd_and_start_io(h, c, DEFAULT_REPLY_QUEUE);
}